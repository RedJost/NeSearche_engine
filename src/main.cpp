#include "ConverterJSON.h"

int main() {
    setlocale(LC_ALL, "English");
    std::vector<std::vector<std::pair<int,float>>> answers;
    std::pair<int, float> a = {1, 23.0f};
    std::pair<int, float> b = {2, 13.2f};
    std::pair<int, float> c = {3, 0.41f};
    std::pair<int, float> d = {4, 0.0f};
    std::pair<int, float> e = {5, 0.0f};
    std::pair<int, float> f = {6, 0.0f};
    std::vector<std::pair<int,float>> lowVec1;
    std::vector<std::pair<int,float>> lowVec2;
    lowVec1.push_back(a);
    lowVec1.push_back(b);
    lowVec1.push_back(c);
    lowVec2.push_back(d);
    lowVec2.push_back(e);
    lowVec2.push_back(f);
    answers.push_back(lowVec1);
    answers.push_back(lowVec2);

    ConverterJSON* myTransl = new ConverterJSON();
    myTransl->putAnswers(answers);

    delete myTransl;
    return 0;
}
