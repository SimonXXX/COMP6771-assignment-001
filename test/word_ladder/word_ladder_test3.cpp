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

// these test look at three and fourletter words using a long and short ladders of various lengths
// also checking that only one letter difference will not affect the output
// a reimplemtation of this program would need the #defines changed as they
// are currently hard coded
// In each section we check that all the ladders are unique and the words in each ladder are unique,
// check that the to and from words are in the correct locations in the ladder,
// check that the length and number of the ladders and that they are correctly sorted,
// also we check a specified ladder is present.
// We also need to test when no word ladder can be found - this is done with perl -> monk

#define TOTAL_WORDS_IN_LEXICON      127142
#define WORDS_IN_LEXICON_3_LETTERS  962
#define WORDS_IN_LEXICON_4_LETTERS  3862

TEST_CASE("Ensure that three letter word ladders are found") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	// require that we have all the lexicon words
	REQUIRE(english_lexicon.size() == TOTAL_WORDS_IN_LEXICON);
	REQUIRE(clexicon{"got",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_3_LETTERS);

	SECTION("Three letters: long ladders : chi -> ego") {

		auto from = std::string{"chi"};
		auto to = std::string{"ego"};
		auto ladder_count = static_cast<unsigned long>(16);
		auto ladder_length = static_cast<unsigned long>(10);

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
		CHECK(ranges::any_of(ladders, testing::contain({"chi","phi","pht","pit","ait","ant","ana","aga","ago","ego"})));
	}

	SECTION("Three letters: short ladders : two letter difference: pee -> pit") {

		auto from = std::string{"pee"};
		auto to = std::string{"pit"};
		auto ladder_count = static_cast<unsigned long>(2);
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
		CHECK(ranges::any_of(ladders, testing::contain({"pee","pie","pit"})));
	}

	SECTION("Three letters: short ladders : one letter difference: fit -> fin") {

		auto from = std::string{"fit"};
		auto to = std::string{"fin"};
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
		CHECK(ranges::any_of(ladders, testing::contain({"fit","fin"})));
	}
}

TEST_CASE("Ensure that four letter word ladders are found") {

	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	// require that we have all the lexicon words
	REQUIRE(english_lexicon.size() == TOTAL_WORDS_IN_LEXICON);
	REQUIRE(clexicon{"work",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_4_LETTERS);

	SECTION("work -> play : many solutions") {

		auto from = std::string{"work"};
		auto to = std::string{"play"};
		auto ladder_count = static_cast<unsigned long>(12);
		auto ladder_length = static_cast<unsigned long>(7);

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
		CHECK(ranges::any_of(ladders, testing::contain({"work", "wort", "wert", "pert", "peat", "plat", "play"})));
	}

	SECTION("sail -> ruin : few solutions") {

		auto from = std::string{"sail"};
		auto to = std::string{"ruin"};
		auto ladder_count = static_cast<unsigned long>(2);
		auto ladder_length = static_cast<unsigned long>(4);

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
		CHECK(ranges::any_of(ladders, testing::contain({"sail", "sain", "rain", "ruin"})));
	}

	SECTION("No solutions (4 chars): perl -> monk") {

		auto ladders = word_ladder::generate("perl", "monk", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}
}