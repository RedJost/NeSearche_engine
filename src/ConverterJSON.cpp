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
