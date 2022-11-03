#include "../include/allExceptions.h"


const char * configException::what() const noexcept {
    return ("config is empty");
}




