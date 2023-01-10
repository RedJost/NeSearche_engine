#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H
#include "allExceptions.h"
#include "nlohmann/json.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>


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

    std::vector<std::string> GetTextDocuments(); // Converts some files.txt in config.json to vector of strings

    int GetResponsesLimit(); // get limit

    std::vector<std::string> GetRequests(); //  Converts requests in config.json to vector of strings

    void putAnswers(std::vector<std::vector<RelativeIndex>> answers); // put relativeIndex (in the end) in answers.json
};







#endif //SEARCH_ENGINE_CONVERTERJSON_H
