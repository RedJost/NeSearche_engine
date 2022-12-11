#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H

#include "InvertedIndex.h"

class SearchServer {
private:
    InvertedIndex myIndex;
public:
    SearchServer(InvertedIndex& inIndex) : myIndex(inIndex){};

    std::vector<std::vector<RelativeIndex>> search (const std::vector<std::string>& requests);
};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
