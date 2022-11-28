#include "SearchServer.h"

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string> &requests) {

    std::vector<std::vector<RelativeIndex>> result;
    std::unordered_set<std::string> uniqueWords; // ИНТЕРЕСУЕТ УНИКАЛЬНОСТЬ СЛОВ

    for (size_t i = 0; i < requests.size(); i++) { // По документам
        std::string requestWord = "";
        for (size_t k = 0; k < requests[i].length(); k++) { // По содержимому (символы в строке)
            if (((requests[i][k] >= '0' && requests[i][k] <= '9') || (requests[i][k] >= 'A' && requests[i][k] <= 'Z') ||
            (requests[i][k] >= 'a' && requests[i][k] <= 'z') || (requests[i][k] == '\'')) && (k != requests[i].length() - 1)) {
                requestWord += (requests[i][k]);
            } else {
                if (requestWord == "") continue; // КРАЙНИЙ СЛУЧАЙ
                if ((k == requests[i].length() - 1) && (requests[i][k] != ' ')) { // КРАЙНИЙ СЛУЧАЙ
                    requestWord += (requests[i][k]);
                }

                uniqueWords.insert(requestWord);
                requestWord = "";
                }
            }
        requestWord = "";
        }

        std::vector<std::pair<std::string, int>> absolutCountOfUniqueWords;
    // СЧЕТЧИК УНИКАЛЬНЫХ СЛОВ ВО ВСЕХ ФАЙЛАХ
        for (auto uniqueIt : uniqueWords) {

            auto infoAboutUniqueWord = myIndex.GetWordCount(uniqueIt);

            int absolutCounter = 0; // СЧЕТЧИК ВХОЖДЕНИЯ ВО ВСЕХ ФАЙЛАХ
            for (auto infoWordIt : infoAboutUniqueWord) {
                absolutCounter += infoWordIt.count;
            }
            std::cout << uniqueIt << std::endl;
            std::cout << absolutCounter << std::endl;

            absolutCountOfUniqueWords.push_back(std::pair<std::string, int>(uniqueIt, absolutCounter));
        }

        // СОРТИРОВКА ВЫБОРКОЙ
        for (int i = 0; i < absolutCountOfUniqueWords.size(); i++) {
            for (int j = 0; j < absolutCountOfUniqueWords.size(); j++) {

                if (absolutCountOfUniqueWords[i].second < absolutCountOfUniqueWords[j].second) {
                    auto temp = absolutCountOfUniqueWords[i];
                    absolutCountOfUniqueWords[i] = absolutCountOfUniqueWords[j];
                    absolutCountOfUniqueWords[j] = temp;
                }
            }
        }

        for (auto it : absolutCountOfUniqueWords) {
            std::cout << "[" << it.first <<  "]: " << it.second <<std::endl;
        }



    return std::vector<std::vector<RelativeIndex>>();
}


