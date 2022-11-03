#include "ConverterJSON.h"

int main() {
    setlocale(LC_ALL, "English");
    ConverterJSON* myTransl = new ConverterJSON();
    std::vector<std::string> myTexts = myTransl->GetTextDocuments();
    for (auto it =  myTexts.begin(); it!= myTexts.end(); it++) {
        std::cout << *it << std::endl;
    }
    delete myTransl;
    return 0;
}
