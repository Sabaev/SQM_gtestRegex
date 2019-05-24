//
// Created by funtik on 05.10.18.
//

#ifndef UNTITLED2_BLACKBOXTEST_H
#define UNTITLED2_BLACKBOXTEST_H

#include "../MyParser.h"
#include <gtest/gtest.h>

struct ParserState {
    std::wstring text;
    std::wstring pattern;
    int64_t  index;
};

struct ParserTest : testing::Test, testing::WithParamInterface<ParserState> {
    std::unique_ptr<MyParser> parser = std::make_unique<MyParser>();
};

struct StarPatternTest:ParserTest{};

TEST_P(StarPatternTest, FindStarPattern) {
auto ps = GetParam();
parser->setPattern(ps.pattern);
auto index = parser->parse(ps.text);
EXPECT_EQ(ps.index, index);
}

INSTANTIATE_TEST_CASE_P(EmptyText, StarPatternTest, testing::Values(
ParserState{L"", L"e*", -1}
));

INSTANTIATE_TEST_CASE_P(OnlyOneCharacterInText, StarPatternTest, testing::Values(
        ParserState{L"aaaaaaaaaaaaaaaaa", L"ab*", 0}
));

INSTANTIATE_TEST_CASE_P(NoPatternInText, StarPatternTest, testing::Values(
        ParserState{L"simple test", L"ae*", -1}
));

struct PlusPatternTest:ParserTest{};

TEST_P(PlusPatternTest, FindPlusPattern) {
    auto ps = GetParam();
    parser->setPattern(ps.pattern);
    auto index = parser->parse(ps.text);
    EXPECT_EQ(ps.index, index);
}

INSTANTIATE_TEST_CASE_P(EmptyText, PlusPatternTest, testing::Values(
        ParserState{L"", L"s+", -1}
));

INSTANTIATE_TEST_CASE_P(OneCharacterText, PlusPatternTest, testing::Values(
        ParserState{L"ppppppppppppp", L"p+", 0}
));

INSTANTIATE_TEST_CASE_P(OneMatchPatterInText, PlusPatternTest, testing::Values(
        ParserState{L"simpleeee test", L"ple+", 3}
));

INSTANTIATE_TEST_CASE_P(NoPatternInText, PlusPatternTest, testing::Values(
        ParserState{L"sim test", L"y+", -1}
));



#endif //UNTITLED2_BLACKBOXTEST_H
