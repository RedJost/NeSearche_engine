#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "allExceptions.h"
#include <unordered_set>


struct RelativeIndex {
    size_t doc_id;
    float rank;
    bool operator == (const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class ConverterJSON {

public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int GetResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<RelativeIndex>> answers);
};







#endif //SEARCH_ENGINE_CONVERTERJSON_H
