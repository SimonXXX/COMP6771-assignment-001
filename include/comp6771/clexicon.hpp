//   COMP6771  Advanced C++ Assignment One
//   =====================================
//        Simon Garrod - z3264122
//   =====================================
//
#ifndef COMP6771_CLEXICON_HPP
#define COMP6771_CLEXICON_HPP

#include <algorithm>
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

class clexicon { // class to encapsulate the manipulation of the lexicon
private:
	std::string const& start_;
	std::string const& end_;
	absl::flat_hash_set<std::string> lexicon_;
	std::vector<std::string> words4removal_;
	bool found_;
	long stringlength_;
	long lexicon_word_count_; // only use for testing

public:
	clexicon(std::string const& a, std::string const& b)
	: start_{a}, end_{b}, lexicon_{}, words4removal_{}, found_{false} {
		stringlength_ = ranges::distance(end_);
	}

	explicit clexicon(std::string const& a,
	                  absl::flat_hash_set<std::string> const& wordlist) // alternative constructor to
	                                                                    // allow testing
	: start_{a}, end_{a}, lexicon_{} {
		stringlength_ = ranges::distance(end_);
		prepare_lexicon(wordlist);
	}

	auto check_assumptions(absl::flat_hash_set<std::string> const& wordlist) -> bool;
	auto prepare_lexicon(absl::flat_hash_set<std::string> const& wordlist) -> void;
	auto list_one_letter_difference(std::string const& target) -> std::vector<std::string>;
	auto get_words() -> std::vector<std::string> {  // these are need to calculate words in
													// next level
		return words4removal_;
	}
	auto get_lexicon_count() -> long {
		return lexicon_word_count_;
	}
	void remove_words();    // remove words as they can appear elsewhere in ladders
	[[nodiscard]] auto end_word_found() -> bool {
		found_ = ranges::find(words4removal_, end_) != words4removal_.end();
		return found_;
	}
}; // of Class clexicon

#endif // COMP6771_CLEXICON_HPP