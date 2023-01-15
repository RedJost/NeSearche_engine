#include "../include/ConverterJSON.h"

std::vector<std::string> ConverterJSON::GetTextDocuments() {

    std::vector<std::string> result;
    std::ifstream configFile;
    configFile.open( "..\\config.json");
    try
    {
        if (configFile.is_open()) {
            nlohmann::json myJson;
            configFile >> myJson;
            auto configuration = myJson.find("config");
            if (configuration != myJson.end()) {
                auto files = myJson.find("files");
                if (files != myJson.end()) {
                    std::string text = "";
                    for (auto curFileName = files->begin(); curFileName != files->end(); curFileName++) {
                        std::ifstream tempFile(*curFileName);
                        if (tempFile.is_open()) {
                            std::string temp = "";
                            while (!tempFile.eof()) {
                                std::getline(tempFile, temp);
                                text = text + temp + '\n';
                            }
                            result.push_back(text);
                            text = "";
                            tempFile.close();
                        } else {
                            std::cout << "WARNING: " << *curFileName << " was not found in directory resources\n";
                        }
                    }
                } else {
                    throw FilesInConfigException();
                }
            } else {
                throw configParameterException();
            }
            configFile.close();

        } else {
            throw configFileException();
        }

    }
    catch(configFileException& er)
    {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    catch (FilesInConfigException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    catch (configParameterException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    return result;
}

int ConverterJSON::GetResponsesLimit() {
    std::ifstream configFile;
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
                throw limitException();
            }
        } else {
            throw configFileException();
        }

    }
    catch (configFileException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    catch (limitException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }

    return 0;
}

std::vector<std::string> ConverterJSON::GetRequests() {
    std::vector<std::string> result;
    std::ifstream requestsFile;
    requestsFile.open("..\\requests.json");
    try {
        if (requestsFile.is_open()) {
            nlohmann::json myJson;
            requestsFile >> myJson;
            auto requests = myJson.find("requests");
            if (requests != myJson.end()) {
                for (auto it = requests->begin(); it != requests->end(); it++) {
                    result.push_back(*it);
                }
            } else {
                throw requestParameterException();
            }
        } else {
            throw requestFileException();
        }
    }
    catch (requestParameterException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    catch (requestFileException& er) {
        std::cout << "Caught an exception: " << er.what() << std::endl;
    }
    requestsFile.close();
    return result;
}

void ConverterJSON::putAnswers(std::vector<std::vector<RelativeIndex>> answers) {
    std::ofstream requestsFile ("..\\answers.json");
    nlohmann::json myJson;
    size_t numberRequest = 1;
    for (int requestIndex = 0; requestIndex < answers.size(); requestIndex++, numberRequest++) {
        std::string nameRequest = "request" + std::to_string(numberRequest);
        if (answers[requestIndex].empty()) {
            myJson[nameRequest]["result"] = "false";
            continue;
        }
        
        for (int docIndex = 0; (docIndex < answers[requestIndex].size()) && (docIndex < GetResponsesLimit()); docIndex++) {
                if (answers[requestIndex][docIndex].rank != 0) {
                myJson[nameRequest]["result"] = "true";
                std::string nameDoc = "docid" + std::to_string(answers[requestIndex][docIndex].doc_id);
                myJson[nameRequest]["relevance"][nameDoc] = answers[requestIndex][docIndex].rank;

            }

        }


    }
    requestsFile << myJson;

    requestsFile.close();
}