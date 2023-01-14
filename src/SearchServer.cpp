#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &requests) {

    std::vector<std::vector<RelativeIndex>> result;

    if (requests.empty()) {
        return std::vector<std::vector<RelativeIndex>>();
    }

    for (size_t requestIndex = 0; requestIndex < requests.size(); requestIndex++) { // REQUESTS
        std::unordered_set<std::string> uniqueWords; // INTERESTED IN THE UNIQUENESS OF WORDS
        // SPLITS THE QUERY INTO UNIQUE WORDS
        std::string requestWord = "";
        for (size_t symbolIndex = 0; symbolIndex < requests[requestIndex].length(); symbolIndex++) { // THE SAME PARSING ALGORITHM AS IN InverterIndex
            if (((requests[requestIndex][symbolIndex] >= '0' && requests[requestIndex][symbolIndex] <= '9') ||
                 (requests[requestIndex][symbolIndex] >= 'A' && requests[requestIndex][symbolIndex] <= 'Z') ||
                 (requests[requestIndex][symbolIndex] >= 'a' && requests[requestIndex][symbolIndex] <= 'z') ||
                 (requests[requestIndex][symbolIndex] == '\'')) && (symbolIndex != requests[requestIndex].length() - 1)) {
                requestWord += (requests[requestIndex][symbolIndex]);
            } else {
                if (requestWord == "") continue;
                if ((symbolIndex == requests[requestIndex].length() - 1) && ((requests[requestIndex][symbolIndex] >= '0' && requests[requestIndex][symbolIndex] <= '9') ||
                                                               (requests[requestIndex][symbolIndex] >= 'A' && requests[requestIndex][symbolIndex] <= 'Z') ||
                                                               (requests[requestIndex][symbolIndex] >= 'a' && requests[requestIndex][symbolIndex] <= 'z'))) {
                    requestWord += (requests[requestIndex][symbolIndex]);
                }

                uniqueWords.insert(requestWord);
                requestWord = "";
            }
        }

        if (uniqueWords.empty()) {
            return std::vector<std::vector<RelativeIndex>>();
        }

        std::vector<std::pair<std::string,std::pair<std::vector<Entry>,int>>> infoUniqueWords; //  std::string - unique word, Entries - information, int - global count, this is main container

        // THE FILLING MAIN CONTAINER
        for (auto uniqueIt : uniqueWords) {
            int globalCount = 0;
            std::vector<Entry> myEntries;
            auto uniqueWord = myIndex.GetWordCount(uniqueIt);
            for (auto wordIt : uniqueWord) {
                myEntries.push_back(wordIt);
                globalCount+=wordIt.count;
            }
            infoUniqueWords.push_back(std::make_pair(uniqueIt,std::make_pair(myEntries,globalCount)));
        }

        if (infoUniqueWords.empty()) {
            return std::vector<std::vector<RelativeIndex>>();
        }

        // SORTING OF ABSOLUTE COUNT IN ASCENDING ORDER
        for (int k = 0; k < infoUniqueWords.size(); k++) {
            for (int j = k; j < infoUniqueWords.size(); j++) {
                if (infoUniqueWords[k].second.second < infoUniqueWords[j].second.second) {
                    std::swap(infoUniqueWords[k],infoUniqueWords[j]);
                }
            }
        }


        // WE GO BY absolutCountOfUniqueWords AND PERFORMING THE SEARCH ALGORITHM

        // STEP 1 - FIND DOCS, WHICH INCLUDED THE RAREST WORD
        auto infoRarestWord = infoUniqueWords.at(0).second.first;
        std::vector<size_t> listDocs; // size_t - DOC_ID
        if (!infoRarestWord.empty()) {
            for (auto docWithRarestWord : infoRarestWord) {
                listDocs.push_back(docWithRarestWord.doc_id);
            }
            //STEP 2 - GO THROUGH THE OTHER WORDS, AND (DELETE DOCUMENTS IN WHICH THEY ARE NOT FROM THIS LIST)*

            if (infoUniqueWords.size() != 1) { // THE REQUEST CAN CONSIST OF ONE WORD, THEN NOTHING NEEDS TO BE DONE
                for (int uniqueWordIndex = 1; uniqueWordIndex < infoUniqueWords.size(); uniqueWordIndex++) {
                    infoRarestWord = infoUniqueWords.at(uniqueWordIndex).second.first;
                    for (int docIndex = 0;  docIndex < listDocs.size(); docIndex++) {
                        bool flagToDelete = true;
                        for (auto& nextEntryIt : infoRarestWord) {
                            if (listDocs[docIndex] == nextEntryIt.doc_id) {
                                flagToDelete = false; // IF UNIQUE WORD INCLUDE DOC_ID, WHICH WE HAVE IN listDocs, THEN DOC_ID WAS NOT DELETED in listDocs
                                break;
                            }
                        }
                        if (flagToDelete) {
                            // DELETING
                            for (int toSave = docIndex; toSave < (listDocs.size() - 1); toSave++) {
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
            for (auto uniqueIt : infoUniqueWords) {
                auto infoUniqueWord = uniqueIt.second.first;
                for (auto entryIt : infoUniqueWord) {
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

        // SORTING WITH STL
        std::sort(curRelativeVector.begin(),curRelativeVector.end(), [](RelativeIndex& first, RelativeIndex& second) {
            return (first.rank > second.rank);
        });

        curRelativeVector.resize(myIndex.getCountDocOutput());

        result.push_back(curRelativeVector);
    }
    return result;
}


