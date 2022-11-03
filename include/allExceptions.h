#ifndef SEARCH_ENGINE_ALLEXCEPTIONS_H
#define SEARCH_ENGINE_ALLEXCEPTIONS_H

#include <exception>

class configException : public std::exception {
    const char *what() const noexcept;
};

#endif //SEARCH_ENGINE_ALLEXCEPTIONS_H
