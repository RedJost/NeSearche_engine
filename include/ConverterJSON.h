
#ifndef SEARCH_ENGINE_CONVERTERJSON_H
#define SEARCH_ENGINE_CONVERTERJSON_H

#include "nlohmann/json.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "allExceptions.h"
#include <sstream>

class ConverterJSON {


public:
    ConverterJSON() = default;

    std::vector<std::string> GetTextDocuments();

    int getResponsesLimit();

    std::vector<std::string> GetRequests();

    void putAnswers(std::vector<std::vector<std::pair<int,float>>> answers);
};


#endif //SEARCH_ENGINE_CONVERTERJSON_H