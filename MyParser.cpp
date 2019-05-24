//
// Created by funtik on 05.10.18.
//

#include "MyParser.h"
#include <set>

bool MyParser::checkPattern(size_t &index, const std::wstring &t){
    size_t state{initState};
    size_t pState{state};
    while (state != 0 && state != 1 && index < t.size()){
        pState = state;
        state = table[t[index]][state];
        ++index;
    }
    return table[endSymbol][state? state: pState] == 1;
}


int64_t MyParser::parse(const std::wstring &text) {
    size_t index{0};
    for (; index < text.size(); ++index) {
        size_t i = index;
        if(checkPattern(i,text)){
            return index;
        } else{
            index = i-1;
        }
    }

    return -1;
}


void clearJumpers(wchar_t c,size_t jState, size_t cState, std::map<wchar_t , std::map<size_t ,size_t >> &table, std::set<size_t > &jumpers) {
    while (jumpers.find(jState) != jumpers.end()) {
        table[c][jState] = cState;
        --jState;

        table[c][jState] = cState;
    }
}



void MyParser::setPattern(const std::wstring &pattern) {
    table.clear();
    std::set<size_t > jumpers;
    if(!pattern.empty()) {
        size_t state{2};
        bool jump = false;
        wchar_t pC{startSymbol};
        for (auto c:pattern) {
            if (c == '*' && state > 2) {
                table[pC][state] = state;
                jumpers.insert(state);
                --state;
                jump = true;
            }
            else if (c == L'+' && state > 2) {
                table[pC][state] = state;
            } else {
                if(jump){
                    clearJumpers(c,state-1,state+2,table,jumpers);
                    table[c][state] = state+2;
                    ++state;
                    table[c][state] = state+1;
                    ++state;
                    jump = false;

                } else if(c != L'*' && c != L'+') {
                    table[c][state] = state + 1;
                    ++state;
                }
                pC = c;
            }
        }
        table[endSymbol][state] = 1;
        if(jump){
            table[endSymbol][state+1] = 1;
        }
        clearJumpers(endSymbol,state-1,1,table,jumpers);
    }
}
