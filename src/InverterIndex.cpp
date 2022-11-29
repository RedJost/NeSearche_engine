#include "InverterIndex.h"

void InverterIndex::UpdateDocumentsBase(std::vector<std::string> inputDocs) {
    setlocale(LC_ALL, "English");

    // ЗАПОЛНЕНИЕ docs ПОКА НЕ ОБНОВЛЯЕТ, А ПЕРЕЗАПИСЫВАЕТ
    docs.resize(inputDocs.size());
    for (size_t i = 0; i < inputDocs.size(); i++) {
        docs[i].first = i;
        docs[i].second = inputDocs[i];
    }
    // ЗАПОЛНЕНИЕ freqDictionary
    for (size_t i = 0; i < docs.size(); i++) { // ПО ДОКУМЕНТАМ
        std::string textTemp = "";
        for (size_t k = 0; k < docs[i].second.length(); k++) { // ПО СИМВОЛАМ В КАЖДОЙ СТРОКЕ-ДОКУМЕНТЕ
            if ( ((docs[i].second[k] >= '0' && docs[i].second[k] <= '9') || (docs[i].second[k] >= 'A' && docs[i].second[k] <= 'Z')
            || (docs[i].second[k] >= 'a' && docs[i].second[k] <= 'z')
            || (docs[i].second[k] == '\'')) && (k != docs[i].second.length() - 1)) {
                textTemp += (docs[i].second[k]);
            } else {
                if (textTemp == "") continue;

                if (k == docs[i].second.length() - 1) {
                    textTemp += (docs[i].second[k]);
                }

                auto wordInDictionary = freqDictionary.find(textTemp);
                if (wordInDictionary == freqDictionary.end()) {
                    std::vector<Entry> tempVectorInfoWord;
                    Entry tempInfoWord;
                    tempInfoWord.doc_id = docs[i].first;
                    tempInfoWord.count = 1;
                    tempVectorInfoWord.push_back(tempInfoWord);
                    freqDictionary[textTemp] = tempVectorInfoWord;
                } else {
                    bool idIsFound = false;
                    for (auto& it : wordInDictionary->second) {
                        if (it.doc_id == docs[i].first) {
                            it.count++;
                            idIsFound = true;
                            break;
                        }
                    }
                    if (!idIsFound) {
                        Entry newEntryInAnotherFile = {docs[i].first, 1};
                        wordInDictionary->second.push_back(newEntryInAnotherFile);
                    }
                }
                textTemp = "";
            }
        }
    }
}

std::vector<Entry> InverterIndex::GetWordCount(const std::string &word) {
    auto wordInDictionary = freqDictionary.find(word);
    if (wordInDictionary != freqDictionary.end()) {
        return wordInDictionary->second;
    }
    return std::vector<Entry>();
}

std::vector<std::pair<size_t,std::string>> InverterIndex::GetDocs() {
    return docs;
}
