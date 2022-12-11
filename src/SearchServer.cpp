#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &requests) {

    std::vector<std::vector<RelativeIndex>> result;

    if (requests.empty()) {
        return std::vector<std::vector<RelativeIndex>>();
    }

    for (size_t i = 0; i < requests.size(); i++) { // REQUESTS(STRINGS)

        std::unordered_set<std::string> uniqueWords; // INTERESTED IN THE UNIQUENESS OF WORDS

        // SPLITS THE QUERY INTO UNIQUE WORDS
        std::string requestWord = "";
        for (size_t k = 0; k < requests[i].length(); k++) { // THE SAME PARSING ALGORITHM AS IN InverterIndex

            if (((requests[i][k] >= '0' && requests[i][k] <= '9') || (requests[i][k] >= 'A' && requests[i][k] <= 'Z') ||
            (requests[i][k] >= 'a' && requests[i][k] <= 'z') || (requests[i][k] == '\'')) && (k != requests[i].length() - 1)) {
                requestWord += (requests[i][k]);
            } else {
                if (requestWord == "") continue;
                if ((k == requests[i].length() - 1) && ((requests[i][k] >= '0' && requests[i][k] <= '9') || (requests[i][k] >= 'A' && requests[i][k] <= 'Z')
                                                        || (requests[i][k] >= 'a' && requests[i][k] <= 'z'))) {
                    requestWord += (requests[i][k]);
                }

                uniqueWords.insert(requestWord);
                requestWord = "";
                }
            }

        if (uniqueWords.empty()) {
            return std::vector<std::vector<RelativeIndex>>();
        }
        // AFTER FILLING IN uniqueWords WE MUST CALCULATE THEIR ABSOLUT COUNT IN ALL DOCS AND GET MAX

        std::vector<std::pair<std::string, int>> absolutCountOfUniqueWords; // A COUNTER OF UNIQUE WORDS IN ALL FILES

        for (auto uniqueIt : uniqueWords) {
            auto infoAboutUniqueWord = myIndex.GetWordCount(uniqueIt);
            int absolutCounter = 0; // GLOBAL COUNT
            for (auto infoWordIt : infoAboutUniqueWord) {
                absolutCounter += infoWordIt.count;
            }
            absolutCountOfUniqueWords.push_back(std::pair<std::string, int>(uniqueIt, absolutCounter));
        }
        // SORTING OF ABSOLUTE COUNT IN ASCENDING ORDER
        for (int k = 0; k < absolutCountOfUniqueWords.size(); k++) {
            for (int j = k; j < absolutCountOfUniqueWords.size(); j++) {
                if (absolutCountOfUniqueWords[k].second < absolutCountOfUniqueWords[j].second) {
                    auto temp = absolutCountOfUniqueWords[k];
                    absolutCountOfUniqueWords[k] = absolutCountOfUniqueWords[j];
                    absolutCountOfUniqueWords[k] = temp;
                }
            }
        }


        // WE GO BY absolutCountOfUniqueWords AND PERFORMING THE SEARCH ALGORITHM

        // STEP 1 - FIND DOCS, WHICH INCLUDED THE RAREST WORD

        auto infoAboutRarestWord = myIndex.GetWordCount(absolutCountOfUniqueWords.at(0).first);
        std::vector<size_t> listDocs; // size_t - DOC_ID

        if (!infoAboutRarestWord.empty()) {
            for (auto it : infoAboutRarestWord) {
                listDocs.push_back(it.doc_id);
            }
            //STEP 2 - GO THROUGH THE OTHER WORDS, AND (DELETE DOCUMENTS IN WHICH THEY ARE NOT FROM THIS LIST)*

            if (absolutCountOfUniqueWords.size() != 1) { // THE REQUEST CAN CONSIST OF ONE WORD, THEN NOTHING NEEDS TO BE DONE
                for (int k = 1; k < absolutCountOfUniqueWords.size(); k++) {
                    infoAboutRarestWord = myIndex.GetWordCount(absolutCountOfUniqueWords.at(k).first);
                    for (int j = 0;  j < listDocs.size(); j++) {
                        bool flagToDelete = true;
                        for (auto& nextEntryIt : infoAboutRarestWord) {
                            if (listDocs[j] == nextEntryIt.doc_id) {
                                flagToDelete = false;
                            }
                        }
                        if (flagToDelete) {
                            // DELETING
                            for (int toSave = j; toSave < (listDocs.size() - 1); toSave++) {
                                listDocs[toSave] = listDocs [toSave+1];
                            }
                            listDocs.resize(listDocs.size()-1);
                        }
                    }
                }
            }

        }


        // CALCULATES RELEVANCE FOR EACH OF THEM

        std::vector<RelativeIndex> curRelativeVector;
        int globalMax = 0;
        for (auto validDocs : listDocs) {
            int local = 0;
            for (auto uniqueIt : absolutCountOfUniqueWords) {
                auto infoAboutUniqueWord = myIndex.GetWordCount(uniqueIt.first);
                for (auto entryIt : infoAboutUniqueWord) {
                    if (validDocs == entryIt.doc_id) {
                        local += entryIt.count;
                    } else continue;
                }
                if (local > globalMax) {
                    globalMax = local;
                }
            }
            RelativeIndex cur;
            cur.doc_id = validDocs;
            cur.rank = (float)local; // JUST TO SAVE LOCAL
            curRelativeVector.push_back(cur);
        }

        // RELATIVITY = LOCAL/GLOBAL_MAX
        for (auto& it : curRelativeVector) {
            it.rank /= globalMax;
        }

        // SORTING
        for (int k = 0; k < curRelativeVector.size(); k++) {
            for (int j = k; j < curRelativeVector.size(); j++) {
                if (curRelativeVector[k].rank < curRelativeVector[j].rank) {
                    auto temp = curRelativeVector[k];
                    curRelativeVector[k] = curRelativeVector[j];
                    curRelativeVector[j] = temp;
                }
            }
        }


        result.push_back(curRelativeVector);
    }
    return result;
}
