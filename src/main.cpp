#include "SearchServer.h"

int main() {
    setlocale(LC_ALL, "English");
    ConverterJSON* myTransl = new ConverterJSON();
    InvertedIndex* myIndex = new InvertedIndex(myTransl->GetResponsesLimit());
    myIndex->UpdateDocumentsBase(myTransl->GetTextDocuments());
    SearchServer* mySearch = new SearchServer(*myIndex);
    myTransl->putAnswers(mySearch->search(myTransl->GetRequests()));

    delete mySearch;
    delete myIndex;
    delete myTransl;

}



