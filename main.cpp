#include <iostream>
#include <gtest/gtest.h>
#include <regex>
#include "test/BlackBoxTest.h"
#include "Parser.h"
#include <chrono>  // for high_resolution_clock
#include <math.h>

void withoutOpt(){
    Parser parser;

    int64_t index{-1};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000 ; ++i) {
        index = parser.parse("tests string for regexgex", "re[gex]+");
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = finish - start;
    std::cout << "Elapsed time: " << duration.count() << " s\n";
    std::cout << index << std::endl;
}

void optimise(){
    ParserStress parser;

    int64_t index{-1};
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000 ; ++i) {
        index = parser.parse("tests string for regexgex", "re[gex]+");
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = finish - start;
    std::cout << "Elapsed time: " << duration.count() << " s\n";
    std::cout << index << std::endl;
}


void wasmRegex(){
    ParserStress parser;
    int64_t index{-1};
    index = parser.parse("tests string for regexgex", "re[gex]+");
    if(index > -1){
        std::cout << "founded, start from index: " + std::to_string(index) << std::endl;
    } else{
        std::cout << "not found" << std::endl;
    }
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}