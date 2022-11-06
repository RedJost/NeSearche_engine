#include "../include/ConverterJSON.h"


std::vector<std::string> ConverterJSON::GetTextDocuments() {
    std::vector<std::string> result;
    std::ifstream configFile;
    configFile.exceptions(std::ios::failbit); // ИСКЛЮЧЕНИЕ НА ОТСТУТСВИЕ ФАЙЛА
    try
    {
        configFile.open( "..\\config.json");
        nlohmann::json myJson;
        configFile >> myJson;
        auto configuration = myJson.find("config");
        if (configuration != myJson.end()) {
            auto files = myJson.find("files");
            if (files != myJson.end()) {
                std::string text = "";
                for (auto it = files->begin(); it != files->end(); it++) {
                    std::ifstream tempFile(*it); // ОПАСНАЯ СТРОЧКА

                    std::string temp;
                    while (!tempFile.eof()) {
                        std::getline(tempFile, temp);
                        text = text + temp + '\n';
                    } // ЧТЕНИЕ ФАЙЛА

                    result.push_back(text);
                    tempFile.close();
                }
            } else {
                std::cout << "NOT FIND FILES\n";
                //throw filesException();
            }
        } else {
            std::cout << "NOT FIND CONFIG\n";
            //throw configException();
        }
        configFile.close();
    }
    catch( std::ios_base::failure er)
    {
        std::cout << "Caught an exception (config file is missing): " << er.what() << std::endl;
    }
    return result;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream configFile;
    configFile.exceptions(std::ios::failbit); // ИСКЛЮЧЕНИЕ НА ОТСТУТСВИЕ ФАЙЛА
    try
    {
        configFile.open( "..\\config.json");
        nlohmann::json myJson;
        configFile >> myJson;
        auto configuration = myJson.find("config");
        if (configuration != myJson.end()) {
            auto limit = configuration->find("max_responses");
            configFile.close();
            if (limit != configuration->end()) {
                return limit.value();
            } else {
                std::cout << "NOT FIND LIMIT\n";
                //throw limitException();
            }
        } else {
            std::cout << "NOT FIND CONFIG\n";
            //throw configException();
        }

    }
    catch( std::ios_base::failure er)
    {
        std::cout << "Caught an exception (config file is missing): " << er.what() << std::endl;
    }

    return 0;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> result;
    std::ifstream requestsFile;
    requestsFile.open("..\\requests.json");
    if (requestsFile.is_open()) {
        nlohmann::json myJson;
        requestsFile >> myJson;
        auto requests = myJson.find("requests");
        if (requests != myJson.end()) {
            for (auto it = requests->begin(); it != requests->end(); it++) {
                result.push_back(*it);
            }

        } else {
            std::cout << "NOT FIND REQUESTS IN FILE\n";
            //throw requestsException
        }

    } else {
        std::cout << "NOT FIND REQUESTS FILE\n";
        //throw requestsFileException
    }
    requestsFile.close();
    return result;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers) {
    std::ofstream requestsFile ("..\\answers.json");
    nlohmann::json myJson;
    int countRequest = 1;
    for (auto it1 = answers.begin(); it1 != answers.end(); it1++, countRequest++) {
        int countForResultOfSearch = 0;
        for (auto it2 = it1->begin(); it2 != it1->end(); it2++) {
            std::string nameRequest = "request" + std::to_string(countRequest);
            if (it2->second == 0) {
                countForResultOfSearch++;
            } else {
                std::string nameDoc = "docid" + std::to_string(it2->first);
                myJson[nameRequest]["relevance"][nameDoc] = it2->second;
            }
            if (countForResultOfSearch == it1->size()) {
                myJson[nameRequest]["result"] = "false";
            } else {
                myJson[nameRequest]["result"] = "true";
            }

        }

    }
    requestsFile << myJson;
    requestsFile.close();

}
