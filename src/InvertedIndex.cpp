#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentsBase(std::vector<std::string> inputDocs) {
    setlocale(LC_ALL, "English");

    // FILLING OUT docs DOES NOT UPDATE YET, BUT OVERWRITES
    docs.resize(inputDocs.size());
    for (size_t idDoc = 0; idDoc < inputDocs.size(); idDoc++) {
        docs[idDoc] = inputDocs[idDoc];
    }
    // FILLING IN THE freqDictionary
    for (size_t idDoc = 0; idDoc < docs.size(); idDoc++) { // ACCORDING TO THE DOCUMENTS
        std::string curWordInDoc = "";
        for (size_t symbolIndex = 0; symbolIndex < docs[idDoc].length(); symbolIndex++) { // BY CHARACTERS IN EACH LINE
            if (((docs[idDoc][symbolIndex] >= '0' && docs[idDoc][symbolIndex] <= '9') || (docs[idDoc][symbolIndex] >= 'A' && docs[idDoc][symbolIndex] <= 'Z')
                 || (docs[idDoc][symbolIndex] >= 'a' && docs[idDoc][symbolIndex] <= 'z')
                 || (docs[idDoc][symbolIndex] == '\'')) && (symbolIndex != docs[idDoc].length() - 1)) { // THE LAST CONDITION IS NECESSARY IN ORDER NOT TO SKIP THE LAST WORD, IT MAY TURN OUT THAT THE LAST CHARACTER BEFORE THE END OF THE LINE AND IT WILL NOT BE ADDED TO THE wordInDictionary
                curWordInDoc += (docs[idDoc][symbolIndex]);
            } else {
                if (curWordInDoc == "") continue;
                if ((symbolIndex == docs[idDoc].length() - 1) && ((docs[idDoc][symbolIndex] >= '0' && docs[idDoc][symbolIndex] <= '9') || (docs[idDoc][symbolIndex] >= 'A' && docs[idDoc][symbolIndex] <= 'Z')
                                                                  || (docs[idDoc][symbolIndex] >= 'a' && docs[idDoc][symbolIndex] <= 'z'))) {
                    curWordInDoc += (docs[idDoc][symbolIndex]); // THIS CONDITION IS NECESSARY TO CHECK THE LAST CHARACTER - IT MUST BE A LETTER \ DIGIT SO THAT THERE IS A WORD
                }

                auto wordInDictionary = freqDictionary.find(curWordInDoc);
                if (wordInDictionary == freqDictionary.end()) {
                    std::vector<Entry> tempVectorInfoWord;
                    Entry tempInfoWord;
                    tempInfoWord.doc_id = idDoc;
                    tempInfoWord.count = 1;
                    tempVectorInfoWord.push_back(tempInfoWord);
                    freqDictionary[curWordInDoc] = tempVectorInfoWord;
                } else {
                    bool idIsFound = false;
                    for (auto& entryOfWord : wordInDictionary->second) {
                        if (entryOfWord.doc_id == idDoc) {
                            entryOfWord.count++;
                            idIsFound = true;
                            break;
                        }
                    }
                    if (!idIsFound) { // THE FIRST OCCURRENCE OF THE FOUND WORD IN ANOTHER FILE (ANOTHER DOC_ID = i)
                        Entry newEntryInAnotherFile = {idDoc, 1};
                        wordInDictionary->second.push_back(newEntryInAnotherFile);
                    }
                }
                curWordInDoc = "";
            }
        }
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string &word) {
    auto wordInDictionary = freqDictionary.find(word);
    if (wordInDictionary != freqDictionary.end()) {
        return wordInDictionary->second;
    }
    return std::vector<Entry>();
}

int InvertedIndex::getCountDocOutput() {
    return countDocOutput;
}




