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

// The tests in this file check that the lexicon application will use all of the words in
// the given lexicon. Also that the assignment assumption are adhered to, if not an empty
// container is retured.
// These are the tests that would be need to be changed if the implementation was changed
// as most of this is hard coded. Other test files are less brittle.
// Test file 2 checks two letter word ladders
// Test file 3 checks three and four letter word ladders
// Test file 4 checks five and more letter word ladders.
// For these test files in each section we check that all the ladders are unique and the words
// in each ladder are unique, that the to and from words are in the correct locations in the ladder,
// that the length and number of the ladders are correct and that they are correctly sorted,
// also we check a specified ladder is present

#define WORDS_IN_LEXICON_2_LETTERS  94      // these defines could be calculated not hard coded
#define WORDS_IN_LEXICON_3_LETTERS  962     // in case we use a different lexicon file
#define WORDS_IN_LEXICON_4_LETTERS  3862
#define WORDS_IN_LEXICON_5_LETTERS  8548
#define WORDS_IN_LEXICON_6_LETTERS  14383
#define WORDS_IN_LEXICON_7_LETTERS  21729
#define WORDS_IN_LEXICON_8_LETTERS  26448
#define WORDS_IN_LEXICON_9_LETTERS  18844
#define WORDS_IN_LEXICON_10_LETTERS 12308
#define WORDS_IN_LEXICON_11_LETTERS 7850
#define WORDS_IN_LEXICON_12_LETTERS 5194
#define WORDS_IN_LEXICON_13_LETTERS 3275
#define WORDS_IN_LEXICON_14_LETTERS 1775
#define WORDS_IN_LEXICON_15_LETTERS 954
#define WORDS_IN_LEXICON_16_LETTERS 495
#define WORDS_IN_LEXICON_17_LETTERS 251
#define WORDS_IN_LEXICON_18_LETTERS 89
#define WORDS_IN_LEXICON_19_LETTERS 48
#define WORDS_IN_LEXICON_20_LETTERS 21
#define WORDS_IN_LEXICON_21_LETTERS 6
#define WORDS_IN_LEXICON_22_LETTERS 3

TEST_CASE("Ensure that all the words in the lexicon file are being used by the word_ladder application") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
	SECTION("check all the words have been found for each word length") {
		CHECK(clexicon{"go",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_2_LETTERS);
		CHECK(clexicon{"got",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_3_LETTERS);
		CHECK(clexicon{"taut",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_4_LETTERS);
		CHECK(clexicon{"whats",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_5_LETTERS);
		CHECK(clexicon{"wooing",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_6_LETTERS);
		CHECK(clexicon{"worries",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_7_LETTERS);
		CHECK(clexicon{"woodchat",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_8_LETTERS);
		CHECK(clexicon{"windswept",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_9_LETTERS);
		CHECK(clexicon{"wantonness",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_10_LETTERS);
		CHECK(clexicon{"waggishness",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_11_LETTERS);
		CHECK(clexicon{"virginalists",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_12_LETTERS);
		CHECK(clexicon{"ventriloquial",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_13_LETTERS);
		CHECK(clexicon{"tintinnabulary",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_14_LETTERS);
		CHECK(clexicon{"repetitiousness",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_15_LETTERS);
		CHECK(clexicon{"perpendicularity",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_16_LETTERS);
		CHECK(clexicon{"photoelectrically",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_17_LETTERS);
		CHECK(clexicon{"phenomenologically",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_18_LETTERS);
		CHECK(clexicon{"extraterritoriality",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_19_LETTERS);
		CHECK(clexicon{"microminiaturization",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_20_LETTERS);
		CHECK(clexicon{"establishmentarianism",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_21_LETTERS);
		CHECK(clexicon{"interdenominationalism",english_lexicon}.get_lexicon_count()== WORDS_IN_LEXICON_22_LETTERS);
	}
}

TEST_CASE("Ensure that application returns empty ladders if assignment assumptions are not "
          "complied with") {
	auto const english_lexicon = word_ladder::read_lexicon("./english.txt");

	SECTION("to and from words unequal length") {
		auto ladders = word_ladder::generate("works", "play", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}

	SECTION("from word not in lexicon") {
		auto ladders = word_ladder::generate("abcd", "play", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}

	SECTION("to word not in lexicon") {
		auto ladders = word_ladder::generate("work", "abcd", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}

	SECTION("to and from word the same") {
		auto ladders = word_ladder::generate("pillow", "pillow", english_lexicon);
		CHECK(ranges::size(ladders) == 0);
	}
}