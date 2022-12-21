
#include <iostream>
#include <string>
#include <vector>
#include "strutils.h"
#include <fstream>
#include <sstream>
#include "HashTable.h"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include <chrono>

using namespace std;


void queryProcessBST(vector<string> & queriedWords, vector<string> & fileNames, BinarySearchTree<WordItem> & BST, bool isCout = false){
    vector<WordItem*> queriedWordItems;
    for(int i = 0; i< queriedWords.size();i++){
        WordItem word(queriedWords[i]);
        BinaryNode<WordItem> * ptr = BST.returnNode(word);
        if(ptr == NULL){
            if(isCout == true)
                cout << "No document contains the given query" << endl;
            return;
        }
        else{
            queriedWordItems.push_back(BST.returnElement(ptr));
        }
    }
    for(int i = 0; i < fileNames.size(); i++){
        int allInTxt = 0;
        for(int j = 0; j < queriedWordItems.size(); j++){
            for(int k = 0; k< queriedWordItems[j]->listDocItem.size(); k++){
                if(queriedWordItems[j]->listDocItem[k].documentName == fileNames[i]){
                    allInTxt++;
                }
            }
        }
        if(allInTxt == queriedWordItems.size()){
            if(isCout == true){
                cout << "in Document " << fileNames[i] << ", ";
                for(int x = 0; x < queriedWordItems.size(); x++){
                    cout << queriedWordItems[x]->word << " found ";
                    for(int y =0; y < queriedWordItems[x]->listDocItem.size(); y++){
                        if(queriedWordItems[x]->listDocItem[y].documentName == fileNames[i]){
                            if(x != queriedWordItems.size()-1){
                                cout << queriedWordItems[x]->listDocItem[y].count << " times, ";
                            }
                            else{
                                cout << queriedWordItems[x]->listDocItem[y].count << " times." << endl;
                            }
                        }
                    }
                }
            }
        }
    }
}

void queryProcessHash(vector<string> & queriedWords, vector<string> & fileNames, HashTable<WordItem> & hTable, bool isCout = false){
    vector<WordItem*> queriedWordItems;
    for(int i = 0; i< queriedWords.size();i++){
        WordItem word(queriedWords[i]);
        WordItem * ptr = &hTable.find(word);
        if(ptr->word == ""){
            if(isCout == true)
                cout << "No document contains the given query" << endl;
            return;
        }
        else{
            queriedWordItems.push_back(ptr);
        }
    }
    for(int i = 0; i < fileNames.size(); i++){
        int allInTxt = 0;
        for(int j = 0; j < queriedWordItems.size(); j++){
            for(int k = 0; k< queriedWordItems[j]->listDocItem.size(); k++){
                if(queriedWordItems[j]->listDocItem[k].documentName == fileNames[i]){
                    allInTxt++;
                }
            }
        }
        if(allInTxt == queriedWordItems.size()){
            if(isCout == true){
                cout << "in Document " << fileNames[i] << ", ";
                for(int x = 0; x < queriedWordItems.size(); x++){
                    cout << queriedWordItems[x]->word << " found ";
                    for(int y =0; y < queriedWordItems[x]->listDocItem.size(); y++){
                        if(queriedWordItems[x]->listDocItem[y].documentName == fileNames[i]){
                            if(x != queriedWordItems.size()-1){
                                cout << queriedWordItems[x]->listDocItem[y].count << " times, ";
                            }
                            else{
                                cout << queriedWordItems[x]->listDocItem[y].count << " times." << endl;
                            }
                        }
                    }
                }
            }
        }
    }
}


int main() {
    WordItem notFound("", "");
    int numFile;
    string fileNameInput;
    cout << "Enter number of input files: ";
    cin >> numFile;
    vector<string> fileNames;
    BinarySearchTree<WordItem> bTree(notFound);
    HashTable<WordItem> hTable(notFound);
    
    for(int i = 1; i<=numFile; i++){
        cout << "Enter " << i << ".  file name: ";
        cin >> fileNameInput;
        fileNames.push_back(fileNameInput);
    }
    
    for(int i = 0; i<fileNames.size(); i++){
        string fileName=fileNames[i];
        ifstream is;
        string line;
        is.open(fileName.c_str());
        string docWord = "";
        while(getline(is, line)){
            istringstream issInput(line);
            string tempWord;
            while(issInput>>tempWord){
                ToLower(tempWord);
                for(int i = 0; i < tempWord.length(); i++){
                    if(isalpha(tempWord[i]))
                        docWord += tempWord[i];
                    else{
                        bool oldFile = false;
                        bool oldFile2 = false;
                        WordItem newWord(docWord, fileName);
                        BinaryNode<WordItem> * ptr = bTree.returnNode(newWord);
                        WordItem * ptr2 = &hTable.find(newWord);
                        
                        if (ptr != NULL&& ptr2->word != ""){
                            vector<DocumentItem> * listPtr  = & bTree.returnElement(ptr)->listDocItem;
                            
                            for(int i = 0; i< listPtr->size(); i++){
                                if((*listPtr)[i].documentName==fileName){
                                    oldFile = true;
                                    (*listPtr)[i].count ++;
                                    docWord = "";
                                }
                            }
                            
                            for(int i = 0; i< ptr2->listDocItem.size(); i++){
                                if(ptr2->listDocItem[i].documentName==fileName){
                                    oldFile2 = true;
                                    ptr2->listDocItem[i].count ++;
                                    docWord = "";
                                }
                            }
                            
                            if(oldFile == false && oldFile2 == false){
                                DocumentItem newDoc(fileName,1);
                                (*listPtr).push_back(newDoc);
                                ptr2->listDocItem.push_back(newDoc);
                                docWord = "";
                            }
                            
                        }
                        else{
                            if(newWord.word != ""){
                                bTree.insert(newWord);
                                hTable.insert(newWord);
                                if(i != tempWord.length()-1)
                                    docWord = "";
                            }
                        }
                    }
                    if(i == tempWord.length()-1 && isalpha(tempWord[i])){
                        bool oldFile = false;
                        bool oldFile2 = false;
                        WordItem newWord(docWord, fileName);
                        BinaryNode<WordItem> * ptr = bTree.returnNode(newWord);
                        WordItem * ptr2 = &hTable.find(newWord);
                        if (ptr != NULL && ptr2->word != ""){
                            vector<DocumentItem> * listPtr  = & bTree.returnElement(ptr)->listDocItem;
                            for(int i = 0; i< listPtr->size(); i++){
                                if((*listPtr)[i].documentName==fileName){
                                    oldFile = true;
                                    (*listPtr)[i].count ++;
                                    docWord = "";
                                }
                            }
                            
                            for(int i = 0; i< ptr2->listDocItem.size(); i++){
                                if(ptr2->listDocItem[i].documentName==fileName){
                                    oldFile2 = true;
                                    ptr2->listDocItem[i].count ++;
                                    docWord = "";
                                }
                            }
                            
                            if(oldFile == false && oldFile2 == false) {
                                DocumentItem newDoc(fileName,1);
                                (*listPtr).push_back(newDoc);
                                ptr2->listDocItem.push_back(newDoc);
                                docWord = "";
                            }
                        }
                        else{
                            if(newWord.word != ""){
                                bTree.insert(newWord);
                                hTable.insert(newWord);
                                docWord = "";
                            }
                        }
                    }
                    if(i == tempWord.length()-1 && isalpha(tempWord[i])==false){
                        docWord = "";
                    }
                }
            }
        }
    }
    cout << "\n\nAfter preprocessing, the unique word count is " << hTable.returnCurrSize() << ". Current load ratio is " << double(hTable.returnCurrSize())/hTable.returnTableSize() << endl;
    
    
    string input;
    cout << "Enter queried words in one line: ";
    cin.get();
    getline(cin, input);
    istringstream queryInput(input);
    string tempWord;
    string queriedWord = "";
    vector<string> queriedWords;
    while(queryInput>>tempWord){
        ToLower(tempWord);
        for(int i = 0; i < tempWord.length(); i++){
            if(isalpha(tempWord[i])){
                queriedWord += tempWord[i];
            }
            else{
                queriedWords.push_back(queriedWord);
                queriedWord = "";
            }
            
            if(i == tempWord.length()-1 && isalpha(tempWord[i])){
                queriedWords.push_back(queriedWord);
                queriedWord = "";
            }
        }
    }

    queryProcessBST(queriedWords, fileNames, bTree, true);
    queryProcessHash(queriedWords, fileNames, hTable, true);
    
    int k = 1000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
      queryProcessBST(queriedWords, fileNames, bTree);
    }
    auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
                    (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << BSTTime.count() / k << "\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < k; i++)
    {
      queryProcessHash(queriedWords, fileNames, hTable);
    }
    auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
                    (std::chrono::high_resolution_clock::now() - start);
    cout << "\nTime: " << HTTime.count() / k << "\n";
    cout << "Speed up: " << (double)BSTTime.count()/HTTime.count() << "\n";

    return 0;
}
