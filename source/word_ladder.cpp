//   COMP6771  Advanced C++ Assignment One
//   =====================================
//        Simon Garrod - z3264122
//   =====================================
//
#include "comp6771/word_ladder.hpp"
#include "comp6771/clexicon.hpp"
#include <algorithm>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "absl/container/flat_hash_set.h"
#include "range/v3/algorithm/copy_if.hpp"
#include "range/v3/algorithm/find.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/view/common.hpp"
#include "range/v3/view/filter.hpp"
#include "range/v3/view/istream.hpp"

namespace word_ladder {

	// Function to generate word ladders from given start and finish words.
	// --------------------------------------------------------------------
	// This uses a clexicon object to manage a lexicon which is initally strips out
	// all words that are not of the required length.
	// The lexican object will then return a series of "word vector" maps containing words
	// one letter different to the key, e.g {"work", {fork, pork, word, worm, worn, wort}}
	// After each level (distance from the start) has had its "word vectors" made the keys (words)
	// are removed from the lexicon to prevent them appearing again in the lexicon. The words in the
	// vectors of the previous level become the keys to the "word vectors" of the next level.
	// Once the end word has been found a recursive function constructs the word ladders from the
	// "word vectors". Or if no more words can be found an empty container is returned.

	auto generate(std::string const& from,
	              std::string const& to,
	              absl::flat_hash_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>> {
		// set up the lexicon object for the from and to words
		clexicon the_lexicon(from, to);
		if (!the_lexicon.check_assumptions(lexicon)) {
			return std::vector<std::vector<std::string>>{};
		}
		the_lexicon.prepare_lexicon(lexicon);

		// get the first vector (list) of words 1 difference to the start word
		// store it in the map nextWordVectors keyed on the start word
		auto next_word_vectors = std::map<std::string, std::vector<std::string>>{};
		next_word_vectors[from] = the_lexicon.list_one_letter_difference(from);
		auto words_this_level = std::vector<std::string>{};
		words_this_level = the_lexicon.get_words(); // get the list of words close to the start words
		the_lexicon.remove_words(); // for this level

		// keep going unil the end word has been found
		while (!the_lexicon.end_word_found() && !words_this_level.empty()) {
			// find all the word vectors for each of the words in this level
			for (std::string const& next_word : words_this_level) {
				if (next_word_vectors[next_word].empty()) {
					next_word_vectors[next_word] = the_lexicon.list_one_letter_difference(next_word);
				}
			}
			// get the words for the next level and delete the words in the level from the lexicon
			words_this_level = the_lexicon.get_words(); // for next level
			the_lexicon.remove_words(); // for this level
		}

		auto ladders = std::vector<std::vector<std::string>>{};
		auto ladder = std::vector<std::string>{};
		if (the_lexicon.end_word_found()) {
			// find the ladders which find the end word
			create_ladders(from, next_word_vectors, ladders, to, ladder); // recursive function
			std::sort(ladders.begin(),
			          ladders.end(),
			          [](std::vector<std::string> const& a, std::vector<std::string> const& b) {
				          return a < b;
			          });
		}
		return ladders;
	}

	// a recursive function to find the word ladders from the "word vectors"
	auto create_ladders(std::string const& word,
	                    std::map<std::string, std::vector<std::string>>& word_lists,
	                    std::vector<std::vector<std::string>>& ladders,
	                    std::string const& finish,
	                    std::vector<std::string>& ladder) -> void {
		ladder.push_back(word);

		for (std::string const& next_word : word_lists[word]) {
			if (word_lists[next_word].empty()) {
				if (next_word == finish) {
					ladder.push_back(finish); // put finish on the end of the ladder
					ladders.push_back(ladder); // we've found a ladder so save it to ladders
					ladder.pop_back(); // take finish off again to stop messing recursion up
					break; // out of for loop
				}
			}
			else {
				create_ladders(next_word, word_lists, ladders, finish, ladder);
			}
		}
		ladder.pop_back(); // remove last word as this at the maximum depth
	}

} // namespace word_ladder
