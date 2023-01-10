#ifndef SEARCH_ENGINE_INVERTEDINDEX_H
#define SEARCH_ENGINE_INVERTEDINDEX_H

#include "ConverterJSON.h"

struct Entry {
    size_t doc_id, count;
    bool operator ==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};


class InvertedIndex {

private:
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> docs;
public:
    InvertedIndex() = default;

    void UpdateDocumentsBase(std::vector<std::string> inputDocs); // update docs and freqDictionary, every word in docs write in freqDictionary, if word was wrote before, then count of this word increased

    std::vector<Entry> GetWordCount(const std::string& word); // get vector of entries 'this word' with doc_id and count of 'this word' in this doc
};


#endif //SEARCH_ENGINE_INVERTEDINDEX_H
