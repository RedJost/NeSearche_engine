//
// Created by u on 19.11.2022.
//

#ifndef SEARCH_ENGINE_INVERTERINDEX_H
#define SEARCH_ENGINE_INVERTERINDEX_H
#include "ConverterJSON.h"

struct Entry {
    size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id &&
                count == other.count);
    }
};

class InverterIndex {
private:

    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> docs;


public:
    InverterIndex() = default;

    void UpdateDocumentsBase(std::vector<std::string> inputDocs);

    std::vector<Entry> GetWordCount(const std::string& word);


};


#endif //SEARCH_ENGINE_INVERTERINDEX_H
