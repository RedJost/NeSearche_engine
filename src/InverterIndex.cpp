#include "InverterIndex.h"

void InverterIndex::UpdateDocumentsBase(std::vector<std::string> inputDocs) {
    setlocale(LC_ALL, "English");

    // ЗАПОЛНЕНИЕ docs ПОКА НЕ ОБНОВЛЯЕТ, А ПЕРЕЗАПИСЫВАЕТ
    docs.resize(inputDocs.size());
    for (size_t i = 0; i < inputDocs.size(); i++) {
        docs[i] = inputDocs[i];
    }
    // ЗАПОЛНЕНИЕ freqDictionary
    for (size_t i = 0; i < docs.size(); i++) { // ПО ДОКУМЕНТАМ
        std::string textTemp = "";
        for (size_t k = 0; k < docs[i].length(); k++) { // ПО СИМВОЛАМ В КАЖДОЙ СТРОКЕ-ДОКУМЕНТЕ
            if ( ((docs[i][k] >= '0' && docs[i][k] <= '9') || (docs[i][k] >= 'A' && docs[i][k] <= 'Z')
            || (docs[i][k] >= 'a' && docs[i][k] <= 'z')
            || (docs[i][k] == '\'')) && (k != docs[i].length() - 1)) {
                textTemp += (docs[i][k]);
            } else {
                if (textTemp == "") continue;

                if (k == docs[i].length() - 1) {
                    textTemp += (docs[i][k]);
                }

                auto wordInDictionary = freqDictionary.find(textTemp);
                if (wordInDictionary == freqDictionary.end()) {
                    std::vector<Entry> tempVectorInfoWord;
                    Entry tempInfoWord;
                    tempInfoWord.doc_id = i;
                    tempInfoWord.count = 1;
                    tempVectorInfoWord.push_back(tempInfoWord);
                    freqDictionary[textTemp] = tempVectorInfoWord;
                } else {
                    bool idIsFound = false;
                    for (auto& it : wordInDictionary->second) {
                        if (it.doc_id == i) {
                            it.count++;
                            idIsFound = true;
                            break;
                        }
                    }
                    if (!idIsFound) {
                        Entry newEntryInAnotherFile = {i, 1};
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


