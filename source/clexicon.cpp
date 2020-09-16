//   COMP6771  Advanced C++ Assignment One
//   =====================================
//        Simon Garrod - z3264122
//   =====================================
//

#include "comp6771/clexicon.hpp"

auto clexicon::check_assumptions(absl::flat_hash_set<std::string> const& wordlist) -> bool {
	// checks that basic assignment assumptions are complied with
	return ((start_.size() == end_.size()) && !wordlist.empty()
	        && ranges::find(wordlist, start_) != wordlist.end()
	        && ranges::find(wordlist, end_) != wordlist.end());
}

auto clexicon::prepare_lexicon(absl::flat_hash_set<std::string> const& wordlist) -> void {
	// creates a lexicon of word of the correct length minus the start word (not needed)
	auto is_right_length = [&](std::string str) { return (ranges::distance(str) == stringlength_); };
	lexicon_ = wordlist | ranges::views::filter(is_right_length)
	           | ranges::to<absl::flat_hash_set<std::string>>;
	lexicon_word_count_ = ranges::distance(lexicon_); // for testing
	lexicon_.erase(start_); // get rid of the start word
}

auto clexicon::list_one_letter_difference(std::string const& target) -> std::vector<std::string> {
	// returns a vector of all the words one letter difference from the target word
	std::vector<std::string> out_list = {};
	for (auto const& check_word : lexicon_) { // check every word left in lexicon
		auto count = 0; // the count of char differences
		// this could probably be optimised with iterators but is efficient as it breaks at 2
		// different chars
		for (unsigned i = 0; (i < stringlength_) and (count < 2); i++) {
			if (check_word.at(i) != target.at(i)) {
				count++;
			}
		}
		if (count == 1) { // check_word is only one charactor different
			out_list.push_back(check_word); // add it to the return vector
			words4removal_.push_back(check_word); // add it to the list of words at this level
		}
	}
	return out_list;
}

void clexicon::remove_words() {
	// removes all words from the lexicon at this level to prevent them appearing again in the
	// ladders
	if (!end_word_found()) { // no point removing words from the lexicon if we are finished
		for (std::string const& wrd2remove : words4removal_) {
			lexicon_.erase(wrd2remove);
		}
		words4removal_.clear(); // ready for the next levels words
	}
}
