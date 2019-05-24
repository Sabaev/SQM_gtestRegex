//
// Created by funtik on 24.05.19.
//

#ifndef TEST_NOTIMPLEMENTEDFEATURESTEST_H
#define TEST_NOTIMPLEMENTEDFEATURESTEST_H
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

struct BlockPatternTest:ParserTest{};

TEST_P(BlockPatternTest, BlockPattern) {
    auto ps = GetParam();
    parser->setPattern(ps.pattern);
    auto index = parser->parse(ps.text);
    EXPECT_EQ(ps.index, index);
}

INSTANTIATE_TEST_CASE_P(BlockWithStar, BlockPatternTest, testing::Values(
        ParserState{L"find some block ", L"[some block]*", 5}
));

INSTANTIATE_TEST_CASE_P(BlocKWithPlus, BlockPatternTest, testing::Values(
        ParserState{L"only one or more some blocks", L"[some block]+", 17}
));

#endif //TEST_NOTIMPLEMENTEDFEATURESTEST_H
