#include "../include/allExceptions.h"


const char *FilesInConfigException::what() const noexcept {
    return ("No files were found in config.json");
}


const char *configParameterException::what() const noexcept {
    return ("'config' parameter wasn't found in config.json");
}

const char *limitException::what() const noexcept {
    return ("'max_responses' parameter wasn't found in config.json");
}

const char *requestParameterException::what() const noexcept {
    return ("'request' parameter wasn't found in request.json");
}

const char *requestFileException::what() const noexcept {
    return ("request.json wasn't found");
}

const char *configFileException::what() const noexcept {
    return ("config.json wasn't found");
}
