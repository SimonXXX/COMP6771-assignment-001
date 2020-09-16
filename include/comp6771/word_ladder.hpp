// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#ifndef COMP6771_WORD_LADDER_HPP
#define COMP6771_WORD_LADDER_HPP

#include <string>
#include <vector>

#include "absl/container/flat_hash_set.h"

namespace word_ladder {
	[[nodiscard]] auto read_lexicon(std::string const& path) -> absl::flat_hash_set<std::string>;

	// Given a start word and destination word, returns all the shortest possible paths from the
	// start word to the destination, where each word in an individual path is a valid word per the
	// provided lexicon. Pre: ranges::size(from) == ranges::size(to) Pre: valid_words.contains(from)
	// and valid_words.contains(to)
	[[nodiscard]] auto generate(std::string const& from,
	                            std::string const& to,
	                            absl::flat_hash_set<std::string> const& lexicon)
	   -> std::vector<std::vector<std::string>>;
	//auto test_function() -> int ;

	auto create_ladders(std::string const& word,
                        std::map<std::string, std::vector<std::string>> & word_lists,
                        std::vector<std::vector<std::string>> & ladders,
                        std::string const& finish,
                        std::vector<std::string> & ladder) -> void;
} // namespace word_ladder

#endif // COMP6771_WORD_LADDER_HPP
