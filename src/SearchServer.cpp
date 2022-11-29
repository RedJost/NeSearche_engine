#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &requests) {
    std::vector<std::vector<RelativeIndex>> result;

    if (requests.empty()) {
        return std::vector<std::vector<RelativeIndex>>();
    }

    for (size_t i = 0; i < requests.size(); i++) { // REQUESTS(STRINGS)
        std::cout << "Request " << i << " :\n";

        std::unordered_set<std::string> uniqueWords; // INTERESTED IN THE UNIQUENESS OF WORDS

        // SPLITS THE QUERY INTO UNIQUE WORDS
        std::string requestWord = "";
        for (size_t k = 0; k < requests[i].length(); k++) { // SYMBOLS
            if (((requests[i][k] >= '0' && requests[i][k] <= '9') || (requests[i][k] >= 'A' && requests[i][k] <= 'Z') ||
            (requests[i][k] >= 'a' && requests[i][k] <= 'z') || (requests[i][k] == '\'')) && (k != requests[i].length() - 1)) {
                requestWord += (requests[i][k]);
            } else {
                if (requestWord == "") continue;
                if ((k == requests[i].length() - 1) && (requests[i][k] != ' ')) {
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

        // SORTING OF ABSOLUTE COUNT IN ASCENDING ORDER AND
        for (int k = 0; k < absolutCountOfUniqueWords.size(); k++) {
            for (int j = 0; j < absolutCountOfUniqueWords.size(); j++) {
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
        std::vector<std::pair<size_t, int>> myDocs;  // size_t - DOC_ID, int - SPECIAL COUNT UNIQUE WORDS, IF HE WILL BE EQUEL COUNT OF UNIQUE WORDS IN REQUEST - THATS GOOD

        if (!infoAboutRarestWord.empty()) {
            for (auto it : infoAboutRarestWord) {
                myDocs.push_back(std::pair<size_t,int>(it.doc_id,1));
            }

            //STEP 2 - GO THROUGH THE OTHER WORDS, AND DELETE DOCUMENTS IN WHICH THEY ARE NOT FROM THIS LIST

            if (absolutCountOfUniqueWords.size() != 1) { // THE REQUEST CAN CONSIST OF ONE WORD, THEN NOTHING NEEDS TO BE DONE
                for (int k = 1; k < absolutCountOfUniqueWords.size(); k++) {
                    infoAboutRarestWord = myIndex.GetWordCount(absolutCountOfUniqueWords.at(k).first);
                    for (auto& nextWordEntryIt : infoAboutRarestWord) {
                        for (auto& listStep1 : myDocs) {
                            if (nextWordEntryIt.doc_id == listStep1.first) {
                                listStep1.second++;
                            }
                        }
                    }
                }
            }
        } else std::cout << "KYKYSIKI\n";


        std::vector<RelativeIndex> curRelativeVector;
        int globalMax = 0;
        for (auto validDocs : myDocs) {
           //std::cout << "[" <<validDocs.first<<"] " << std::endl;
            int local = 0;
            for (auto uniqueIt : absolutCountOfUniqueWords) {
                //std::cout << uniqueIt.first << " " << std::endl;
                auto infoAboutUniqueWord = myIndex.GetWordCount(uniqueIt.first);
                for (auto entryIt : infoAboutUniqueWord) {
                    if (validDocs.second == absolutCountOfUniqueWords.size() && validDocs.first == entryIt.doc_id) {
                        local += entryIt.count;
                        //std::cout << local << std::endl;
                    }
                }
                if (local > globalMax) {
                    globalMax = local;
                }
            }
            RelativeIndex cur;
            cur.doc_id = validDocs.first;
            cur.rank = (float)local; // JUST TO SAVE LOCAL
            curRelativeVector.push_back(cur);
        }

        for (auto& it : curRelativeVector) {
            it.rank /= globalMax;
        }

        result.push_back(curRelativeVector);
    }
    return result;
}








//std::vector<std::pair<size_t,std::string>> surve = myIndex.GetDocs();
//for (auto wordsIt : absolutCountOfUniqueWords) {
//auto curRarestWord = wordsIt.first;
//auto InfoAboutRarest = myIndex.GetWordCount(curRarestWord);
//for (auto entryIt : InfoAboutRarest) {
//auto curId = entryIt.doc_id;
//
//
//}
//}