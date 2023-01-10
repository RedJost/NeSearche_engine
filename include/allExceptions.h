#ifndef SEARCH_ENGINE_ALLEXCEPTIONS_H
#define SEARCH_ENGINE_ALLEXCEPTIONS_H
#include <exception>

class FilesInConfigException : public std::exception {
public:
    const char *what() const noexcept;
};

class configParameterException : public std::exception {
public:
    const char *what() const noexcept;
};

class limitException : public std::exception {
public:
    const char *what() const noexcept;
};

class configFileException : public std::exception {
public:
    const char *what() const noexcept;
};

class requestParameterException : public std::exception {
public:
    const char *what() const noexcept;
};

class requestFileException : public std::exception {
public:
    const char *what() const noexcept;
};


#endif //SEARCH_ENGINE_ALLEXCEPTIONS_H
