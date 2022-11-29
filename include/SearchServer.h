
#ifndef SEARCH_ENGINE_SEARCHSERVER_H
#define SEARCH_ENGINE_SEARCHSERVER_H
#include "InverterIndex.h"

struct RelativeIndex {
    size_t doc_id;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};


class SearchServer {
private:
    InverterIndex myIndex;

public:
    SearchServer(InverterIndex& inIndex) : myIndex(inIndex){};

    std::vector<std::vector<RelativeIndex>> search (const std::vector<std::string>& requests);

};


#endif //SEARCH_ENGINE_SEARCHSERVER_H
