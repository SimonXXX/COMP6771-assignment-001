//
//  Copyright UNSW Sydney School of Computer Science and Engineering
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "comp6771/word_ladder.hpp"
#include "comp6771/clexicon.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/all_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/range/primitives.hpp"
#include "range/v3/algorithm/unique.hpp"
#include <iostream>

// These test look at two letter words using a ladders of various lengths,
// also checking that only one letter difference will not affect the output
// A reimplemtation of this program would need the #defines changed as they
// are currently hard coded.
// In each section we check that all the ladders are unique and the words in each ladder are unique,
// check that the to and from words are in the correct locations in the ladder,
// check that the length and number of the ladders and that they are correctly sorted,
// also we check a specified ladder is present.

#define TOTAL_WORDS_IN_LEXICON      127142
#define WORDS_IN_LEXICON_2_LETTERS  94

TEST_CASE("Ensure that two letter word ladders are found") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	// require that we have all the lexicon words
	REQUIRE(english_lexicon.size() == TOTAL_WORDS_IN_LEXICON);
	REQUIRE(clexicon{"go",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_2_LETTERS);

	SECTION("Two letters: long ladders : go -> if") {

		auto from = std::string{"go"};
		auto to = std::string{"if"};
		auto ladder_count = static_cast<unsigned long>(14);
		auto ladder_length = static_cast<unsigned long>(6);

		auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end() );
		CHECK(ranges::all_of(ladders,[](auto ladder){return (ranges::unique(ladder) == ladder.end());} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.front() == from);} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.back() == to);} ));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ranges::size(ladder) == ladder_length);} ));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"go","wo","we","oe","of","if"})));
	}

	SECTION("Two letters: short ladders : go -> so  : one letter difference") {

		auto from = std::string{"go"};
		auto to = std::string{"do"};
		auto ladder_count = static_cast<unsigned long>(1);
		auto ladder_length = static_cast<unsigned long>(2);

		auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end() );
		CHECK(ranges::all_of(ladders,[](auto ladder){return (ranges::unique(ladder) == ladder.end());} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.front() == from);} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.back() == to);} ));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ranges::size(ladder) == ladder_length);} ));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"go","do"})));
	}

	SECTION("Two letters: short ladders : oh -> be  : two letter difference") {

		auto from = std::string{"oh"};
		auto to = std::string{"be"};
		auto ladder_count = static_cast<unsigned long>(1);
		auto ladder_length = static_cast<unsigned long>(3);

		auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end() );
		CHECK(ranges::all_of(ladders,[](auto ladder){return (ranges::unique(ladder) == ladder.end());} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.front() == from);} ));
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ladder.back() == to);} ));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,[&](auto ladder){return (ranges::size(ladder) == ladder_length);} ));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders, testing::contain({"oh","oe","be"})));
	}
}
