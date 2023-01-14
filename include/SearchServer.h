#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include "InvertedIndex.h"

class SearchServer {
private:
    InvertedIndex myIndex;
public:

    SearchServer(InvertedIndex& inIndex) : myIndex(inIndex){};

    std::vector<std::vector<RelativeIndex>> search (const std::vector<std::string>& requests); // allot unique words in const request and found their in freqDictionary of InvertedIndex
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
