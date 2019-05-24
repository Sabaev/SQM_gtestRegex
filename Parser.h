//
// Created by funtik on 03.10.18.
//

#ifndef UNTITLED2_PARSER_H
#define UNTITLED2_PARSER_H

#include <regex>

struct ParserStress {
    int64_t parse(const std::string &text, const std::string &pattern) {
        static std::string hashPattern{};
        static int64_t hashIndex{-1};
        if(hashPattern == pattern){
            return hashIndex;
        }
        hashPattern = pattern;
        std::regex e(pattern);
        std::smatch m;
        if(std::regex_search(text, m, e)){
            hashIndex = m.position(0);
            return hashIndex;
        }
        hashIndex = -1;
        return hashIndex;
    }

};


struct Parser {
    int64_t parse(const std::string &text, const std::string &pattern) {
        std::regex e(pattern);
        std::smatch m;
        if(std::regex_search(text, m, e)){
            return m.position(0);
        }
        return -1;
    }

};

#endif //UNTITLED2_PARSER_H
