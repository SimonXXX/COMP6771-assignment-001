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
#include "comp6771/clexicon.hpp"
#include "comp6771/word_ladder.hpp"

#include <string>
#include <vector>

#include "catch2/catch.hpp"
#include "comp6771/testing/range/contain.hpp"
#include "range/v3/algorithm/all_of.hpp"
#include "range/v3/algorithm/any_of.hpp"
#include "range/v3/algorithm/is_sorted.hpp"
#include "range/v3/algorithm/unique.hpp"
#include "range/v3/range/conversion.hpp"
#include "range/v3/range/primitives.hpp"
#include <iostream>

// These test look at five letter words which produce ladders of various lengths.
// also look at a few longer words including those that have no ladder solutions.
// A reimplemtation of this program would need the #defines changed as they
// are currently hard coded.
// In each section we check that all the ladders are unique and the words in each ladder are unique,
// check that the to and from words are in the correct locations in the ladder,
// check that the length and number of the ladders and that they are correctly sorted,
// also we check a specified ladder is present.
// We also need to test when no word ladder can be found.

#define TOTAL_WORDS_IN_LEXICON 127142
#define WORDS_IN_LEXICON_5_LETTERS 8548
#define WORDS_IN_LEXICON_9_LETTERS  18844
#define WORDS_IN_LEXICON_11_LETTERS 7850
#define WORDS_IN_LEXICON_15_LETTERS 954

TEST_CASE("Ensure that five letter word ladders are found") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	// require that we have all the lexicon words
	REQUIRE(english_lexicon.size() == TOTAL_WORDS_IN_LEXICON);
	REQUIRE(clexicon{"windy", english_lexicon}.get_lexicon_count() == WORDS_IN_LEXICON_5_LETTERS);

	SECTION("Five letters: long ladders : nylon -> idler") {
		auto from = std::string{"nylon"};
		auto to = std::string{"idler"};
		auto ladder_count = static_cast<unsigned long>(12);
		auto ladder_length = static_cast<unsigned long>(30);

		auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end());
		CHECK(ranges::all_of(ladders,
		                     [](auto ladder) { return (ranges::unique(ladder) == ladder.end()); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.front() == from); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.back() == to); }));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,
		                     [&](auto ladder) { return (ranges::size(ladder) == ladder_length); }));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		   testing::contain({"nylon", "pylon", "pelon", "melon", "meson", "mason", "macon", "racon",
		                     "recon", "redon", "redos", "redes", "rides", "sides", "sires", "siree",
		                     "spree", "sprue", "sprug", "sprig", "sprit", "split", "uplit", "unlit",
		                     "unlet", "inlet", "islet", "isles", "idles", "idler"})));
	}

	SECTION("Five letters: short ladders : melon -> mason") {
		auto from = std::string{"melon"};
		auto to = std::string{"mason"};
		auto ladder_count = static_cast<unsigned long>(1);
		auto ladder_length = static_cast<unsigned long>(3);

		auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end());
		CHECK(ranges::all_of(ladders,
		                     [](auto ladder) { return (ranges::unique(ladder) == ladder.end()); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.front() == from); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.back() == to); }));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,
		                     [&](auto ladder) { return (ranges::size(ladder) == ladder_length); }));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,testing::contain({"melon", "meson", "mason"})));
	}

	SECTION("No solutions (5 chars): aloof -> earth") {
		auto ladders = word_ladder::generate("aloof", "earth", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}
}

TEST_CASE("Ensure that longer word ladders are found") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	// require that we have all the lexicon words
	REQUIRE(english_lexicon.size() == TOTAL_WORDS_IN_LEXICON);
	REQUIRE(clexicon{"decanting", english_lexicon}.get_lexicon_count() == WORDS_IN_LEXICON_9_LETTERS);

	SECTION("Nine letters: long ladders : decanting -> derailing") {
		auto from = std::string{"decanting"};
		auto to = std::string{"derailing"};
		auto ladder_count = static_cast<unsigned long>(6);
		auto ladder_length = static_cast<unsigned long>(18);

    	auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end());
		CHECK(ranges::all_of(ladders,
		                     [](auto ladder) { return (ranges::unique(ladder) == ladder.end()); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.front() == from); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.back() == to); }));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,
		                     [&](auto ladder) { return (ranges::size(ladder) == ladder_length); }));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		   testing::contain({"decanting", "recanting", "recasting", "retasting", "retesting",
		                        "revesting", "revetting", "reletting", "relenting", "relending",
		                        "remending", "remanding", "remanning", "remaining", "retaining",
		                        "retailing", "detailing", "derailing"})));
	}

	SECTION("No solutions (11 chars): sillinesses -> wackinessess") {
		REQUIRE(clexicon{"sillinesses", english_lexicon}.get_lexicon_count() == WORDS_IN_LEXICON_11_LETTERS);
		auto ladders = word_ladder::generate("sillinesses", "wackinessess", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}

	SECTION("Fifteen letters: sentimentalized -> sentimentalizes") {
		REQUIRE(clexicon{"sentimentalized", english_lexicon}.get_lexicon_count() == WORDS_IN_LEXICON_15_LETTERS);

		auto from = std::string{"sentimentalized"};
		auto to = std::string{"sentimentalizes"};
		auto ladder_count = static_cast<unsigned long>(1);
		auto ladder_length = static_cast<unsigned long>(2);

    	auto ladders = word_ladder::generate(from, to, english_lexicon);

		// check that all the ladders are unique and the words in each ladder are unique
		// check that the to and from words are in the correct locations in the ladder
		// check that the length and number of the ladders and that they are correctly sorted
		// check a specified ladder is present
		CHECK(ranges::unique(ladders) == ladders.end());
		CHECK(ranges::all_of(ladders,
		                     [](auto ladder) { return (ranges::unique(ladder) == ladder.end()); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.front() == from); }));
		CHECK(ranges::all_of(ladders, [&](auto ladder) { return (ladder.back() == to); }));
		CHECK(ranges::size(ladders) == ladder_count);
		CHECK(ranges::all_of(ladders,
		                     [&](auto ladder) { return (ranges::size(ladder) == ladder_length); }));
		CHECK(ranges::is_sorted(ladders));
		CHECK(ranges::any_of(ladders,
		   testing::contain({"sentimentalized", "sentimentalizes"})));
	}
}