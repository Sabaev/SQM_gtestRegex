//
// Created by funtik on 06.10.18.
//

#ifndef UNTITLED2_WHITEBOXTEST_H
#define UNTITLED2_WHITEBOXTEST_H

#include "MyParser.h"
#include <gtest/gtest.h>

struct MyParserState {
    std::string text;
    std::string pattern;
    int64_t  index;

};

struct MyParserTest : testing::Test, testing::WithParamInterface<MyParserState> {
    std::unique_ptr<MyParser> parser = std::make_unique<MyParser>();
};


TEST_P(MyParserTest, FindPattern) {
    auto ps = GetParam();
    parser->setPattern(ps.pattern);
    auto index = parser->parse(ps.text);
    EXPECT_EQ(ps.index, index);
}

INSTANTIATE_TEST_CASE_P(StarPatternEmptyText, MyParserTest, testing::Values(
        MyParserState{"", "ple*", -1}
));

INSTANTIATE_TEST_CASE_P(StarPatternOnlyOneCharacterInText, MyParserTest, testing::Values(
        MyParserState{"aaaaaaaaaaaaaaaaa", "a*", 0}
));

INSTANTIATE_TEST_CASE_P(StarPatternMultiStarTest, MyParserTest, testing::Values(
        MyParserState{"simple test", "si*h*", 0}
));

INSTANTIATE_TEST_CASE_P(MultiStarAtTheEndTest, MyParserTest, testing::Values(
        MyParserState{"12343567ab", "ai*h*t*b*", 8}
));


INSTANTIATE_TEST_CASE_P(PlusTest, MyParserTest, testing::Values(
        MyParserState{"simple test", "so+", -1}
));

INSTANTIATE_TEST_CASE_P(MultiPlusTest, MyParserTest, testing::Values(
        MyParserState{"simple test", "si+m+", 0}
));


#endif //UNTITLED2_WHITEBOXTEST_H
