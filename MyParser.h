#include <utility>

//
// Created by funtik on 05.10.18.
//

#ifndef UNTITLED2_MYPARSER_H
#define UNTITLED2_MYPARSER_H


#include <string>
#include <map>

struct MyParser {
    MyParser() = default;

    void setPattern(const std::wstring &pattern);

    int64_t parse(const std::wstring &text);

private:
    std::map<char, std::map<size_t, size_t >> table;
    wchar_t startSymbol = '\02';
    wchar_t endSymbol = '\0';
    size_t initState{2};

    bool checkPattern(size_t &index, const std::wstring &t);
};


#endif //UNTITLED2_MYPARSER_H
