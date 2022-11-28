#include "SearchServer.h"

//#include "gtest/gtest.h"


int main() {
    setlocale(LC_ALL, "English");
    ConverterJSON* myTransl = new ConverterJSON();
    InverterIndex* myIndex = new InverterIndex();
    myIndex->UpdateDocumentsBase(myTransl->GetTextDocuments());
    SearchServer* mySearch = new SearchServer(*myIndex);
    mySearch->search(myTransl->GetRequests());


    delete mySearch;
    delete myIndex;
    delete myTransl;
    return 0;
}


//myIndex->UpdateDocumentsBase(myTransl->GetTextDocuments());
//    for (auto it : myIndex->freqDictionary) {
//        std::cout << it.first << " in " << std::endl;
//        for (int i = 0; i < it.second.size(); i++) {
//        std::cout << "["<< it.second[i].doc_id <<"]" << " has " << it.second[i].count << std::endl;
//        }
//}
