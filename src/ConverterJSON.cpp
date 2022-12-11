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
                    std::string temp = "";
                    while (!tempFile.eof()) {
                        std::getline(tempFile, temp);
                        text = text + temp + '\n';
                    } // ЧТЕНИЕ ФАЙЛА
                    result.push_back(text);
                    text = "";
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

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    std::ofstream requestsFile ("..\\answers.json");
    nlohmann::json myJson;
    size_t numberRequest = 1;
    for (auto requestIt = answers.begin(); requestIt != answers.end(); requestIt++, numberRequest++) {
        std::string nameRequest = "request" + std::to_string(numberRequest);
        if (requestIt->empty()) {
            myJson[nameRequest]["result"] = "false";
            continue;
        }
        for (auto docsIt = requestIt->begin(); docsIt != requestIt->end(); docsIt++) {
                if (docsIt->rank != 0) {
                myJson[nameRequest]["result"] = "true";
                std::string nameDoc = "docid" + std::to_string(docsIt->doc_id);
                myJson[nameRequest]["relevance"][nameDoc] = docsIt->rank;
            }
        }

    }
    requestsFile << myJson;
    requestsFile.close();
}