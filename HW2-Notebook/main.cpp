
#include <iostream>
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "AvlTree.h"
#include "AvlTree.cpp"
#include <fstream>
#include <sstream>
#include <string>
#pragma comment(linker, "/STACK:5000000")
#pragma comment(linker, "/HEAP:5000000")
using namespace std;

int main() {
    long long timerBST = 0;
    long long timerAVL = 0;
    cout << "Welcome to the Notebook!\n\n";
    ifstream is;
    string fileName = "data.txt";
    string dataLine, sectionTitle, input, input2;
    is.open(fileName.c_str());
    string notFound = "not found";
    BinarySearchTree<string, BinarySearchTree<string,string>*> sectionsBST(notFound);
    AvlTree<string,AvlTree<string,string>*> sectionsAVL(notFound);
    bool isFirstSection = true;
    string oldSection;
    while (getline(is, dataLine)){
        string itemTitle, itemInfo;
        istringstream issInput(dataLine);
        issInput>> input;
        
        if(input[0] != '-'){
            sectionTitle = input;
            BinarySearchTree<string, string> * ptrItemTreeBST = new BinarySearchTree<string, string>(notFound);
            AvlTree<string, string> * ptrItemTreeAVL = new AvlTree<string, string>(notFound);
            auto start = std::chrono::high_resolution_clock::now();
            sectionsBST.insert(sectionTitle, ptrItemTreeBST);
            auto end = std::chrono::high_resolution_clock::now();
            timerBST += (end-start).count() / 1000.0;
            
            auto start2 = std::chrono::high_resolution_clock::now();
            sectionsAVL.insert(sectionTitle, ptrItemTreeAVL);
            auto end2 = std::chrono::high_resolution_clock::now();
            timerAVL += (end2-start2).count() / 1000.0;
            
            if(isFirstSection == true){
                oldSection = input;
            }
            else{
                cout << "Section \"" << oldSection << "\" has been inserted into the BST notebook.\n";
                cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl << endl;
                timerBST = 0;
                timerAVL = 0;
                oldSection = input;
            }
            isFirstSection = false;
        }
        else{
            if(input.rfind('-')!=0){
                itemTitle = input.substr(1, input.rfind('-')-1);
                itemInfo += input.substr(input.rfind('-')+1, input.length());
                while(issInput>>input2){
                    itemInfo += ' ' + input2;
                }
            }
            else{
                itemTitle += input.substr(1, input.length());
                issInput>>input2;
                while(input2.find('-') == string::npos){
                    itemTitle += ' ' + input2;
                    issInput>>input2;
                }
                itemTitle += ' ' + input2;
                itemTitle = itemTitle.substr(0, itemTitle.find('-'));
                itemInfo += input2.substr(input2.find('-')+1, input2.length());
                while(issInput>>input2){
                    itemInfo += ' ' + input2;
                }
            }
            auto start = std::chrono::high_resolution_clock::now();
            BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(sectionTitle);
            sectionsBST.returnRest(sectionNodePtr)->insert(itemTitle, itemInfo);
            auto end = std::chrono::high_resolution_clock::now();
            timerBST += (end-start).count() / 1000.0;
            
            auto start2 = std::chrono::high_resolution_clock::now();
            AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(sectionTitle);
            sectionsAVL.returnRest(sectionNodePtrAvl)->insert(itemTitle, itemInfo);
            auto end2 = std::chrono::high_resolution_clock::now();
            timerAVL += (end2-start2).count() / 1000.0;
        }
    }
    cout << "Section \"" << oldSection << "\" has been inserted into the BST notebook.\n";
    cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
    cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
    timerBST = 0;
    timerAVL = 0;
    
    int choice;
    cout << "\n\nMENU\nPlease enter an input between [1 - 6]:\n1- Display the sections [AVL]\n2- Display the sections [BST]\n3- Select a section\n4- Add new section\n5- Delete a section\n6- Exit\nInput: ";
    cin >> choice;
    
    while(choice != 6) {
        cout << "\n";
        
        if (choice==1) {
            cout << "*****\n";
            sectionsAVL.printTree();
            cout << "*****\n";        }
        
        else if (choice==2){
            cout << "*****\n";
            sectionsBST.printTree();
            cout << "*****\n";
        }
        
        else if (choice==3){
            string choosenTitle;
            cout << "Enter the title of the section: ";
            cin >> choosenTitle;
            
            if(sectionsBST.returnNode(choosenTitle)==NULL && sectionsAVL.returnNode(choosenTitle)==NULL){
                cout << "Invalid title!\n";
            }
            
            else{
                int choice2;
                cout << "Selected section -> " << choosenTitle << endl;
                cout << "Please enter an input between [1 - 7]:\n1- Display the items [AVL]\n2- Display the items [BST]\n3- Display the information of a item\n4- Add new item\n5- Update the information of a item\n6- Delete an item\n7- Return to main menu";
                cout << "\nInput: ";
                cin >> choice2;
                while(choice2 != 7) {
                    if (choice2 == 1) {
                        AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(choosenTitle);
                        AvlTree<string, string> * selectedItemTreeAvl = sectionsAVL.returnRest(sectionNodePtrAvl);
                        cout << "\n*****\n";
                        selectedItemTreeAvl->printTree();
                        cout << "*****\n";
                    }
                    
                    else if (choice2 == 2) {
                        BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(choosenTitle);
                        BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                        cout << "\n*****\n";
                        selectedItemTree->printTree();
                        cout << "*****\n";
                    }
                    
                    else if (choice2 == 3) {
                        string itemTitle;
                        cout << "Enter the title of the item: ";
                        cin.get();
                        getline(cin, itemTitle);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(choosenTitle);
                        BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                        BinaryNode<string, string> * itemPtr = selectedItemTree->returnNode(itemTitle);
                        auto end = std::chrono::high_resolution_clock::now();
                        timerBST += (end-start).count() / 1000.0;
                        
                        
                        auto start2 = std::chrono::high_resolution_clock::now();
                        AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(choosenTitle);
                        AvlTree<string, string> * selectedItemTreeAvl = sectionsAVL.returnRest(sectionNodePtrAvl);
                        AvlNode<string, string> * itemPtrAvl = selectedItemTreeAvl->returnNode(itemTitle);
                        auto end2 = std::chrono::high_resolution_clock::now();
                        timerAVL += (end2-start2).count() / 1000.0;

                        if (itemPtr == NULL && itemPtrAvl == NULL) {
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            cout << "Invalid title.\n";
                            //break;
                        }
                        
                        else{
                            auto start = std::chrono::high_resolution_clock::now();
                            string choosenInfo = selectedItemTree->returnRest(itemPtr);
                            auto end = std::chrono::high_resolution_clock::now();
                            timerBST += (end-start).count() / 1000.0;
                            
                            auto start2 = std::chrono::high_resolution_clock::now();
                            string choosenInfo2 = selectedItemTreeAvl->returnRest(itemPtrAvl);
                            auto end2 = std::chrono::high_resolution_clock::now();
                            timerBST += (end2-start2).count() / 1000.0;
                            
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            cout << choosenInfo << "\n";
                        }
                        
                    }
                    else if (choice2 == 4) {
                        
                        string newItemTitle;
                        cout << "Enter the title of the item: ";
                        cin.get();
                        getline(cin, newItemTitle);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(choosenTitle);
                        BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                        BinaryNode<string, string> * itemPtr = selectedItemTree->returnNode(newItemTitle);
                        auto end = std::chrono::high_resolution_clock::now();
                        timerBST += (end-start).count() / 1000.0;
                        
                        auto start2 = std::chrono::high_resolution_clock::now();
                        AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(choosenTitle);
                        AvlTree<string, string> * selectedItemTreeAvl = sectionsAVL.returnRest(sectionNodePtrAvl);
                        AvlNode<string, string> * itemPtrAvl = selectedItemTreeAvl->returnNode(newItemTitle);
                        auto end2 = std::chrono::high_resolution_clock::now();
                        timerAVL += (end2-start2).count() / 1000.0;
                        
                        if (itemPtr != NULL && itemPtrAvl != NULL) {
                            cout << "Item \"" << newItemTitle << "\" already exists in the \"" << choosenTitle << "\".\n";
                        }
                        
                        else{
                            string newItemInfo;
                            cout << "Enter a description for the item: ";
                            getline(cin, newItemInfo);
                            auto start = std::chrono::high_resolution_clock::now();
                            selectedItemTree->insert(newItemTitle, newItemInfo);
                            auto end = std::chrono::high_resolution_clock::now();
                            timerBST += (end-start).count() / 1000.0;
                            //DO SAME FOR AVL
                            
                            auto start2 = std::chrono::high_resolution_clock::now();
                            selectedItemTreeAvl->insert(newItemTitle, newItemInfo);
                            auto end2 = std::chrono::high_resolution_clock::now();
                            timerAVL += (end2-start2).count() / 1000.0;
                            
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            
                            cout << "The new item \"" << newItemTitle << "\" has been inserted." << endl;
                        }
                    }
                    else if (choice2 == 5) {
                        string itemUpdated;
                        cout << "Enter the title of the item: ";
                        cin.get();
                        getline(cin, itemUpdated);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(choosenTitle);
                        BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                        BinaryNode<string, string> * itemPtr = selectedItemTree->returnNode(itemUpdated);
                        auto end = std::chrono::high_resolution_clock::now();
                        timerBST += (end-start).count() / 1000.0;
                        //DO SAME FOR AVL
                        
                        auto start2 = std::chrono::high_resolution_clock::now();
                        AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(choosenTitle);
                        AvlTree<string, string> * selectedItemTreeAvl = sectionsAVL.returnRest(sectionNodePtrAvl);
                        AvlNode<string, string> * itemPtrAvl = selectedItemTreeAvl->returnNode(itemUpdated);
                        auto end2 = std::chrono::high_resolution_clock::now();
                        timerAVL += (end2-start2).count() / 1000.0;
                        
                        if (itemPtr == NULL && itemPtrAvl == NULL) {
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            cout << "Item \"" << itemUpdated << "\" does not exist in the \"" << choosenTitle << "\"." << endl;
                        }
                        else{
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            string infoUpdated;
                            cout << "Enter the new information: ";
                            getline(cin, infoUpdated);
                            selectedItemTree->updateItemRest(itemPtr, infoUpdated);
                            selectedItemTreeAvl->updateItemRest(itemPtrAvl, infoUpdated);
                            cout << "The content " << itemUpdated << " has been updated." << endl;
                        }
                    }
                    else if (choice2 == 6) {
                        string itemDeleted;
                        cout << "Enter the title of the item: ";
                        cin.get();
                        getline(cin, itemDeleted);
                        
                        auto start = std::chrono::high_resolution_clock::now();
                        BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(choosenTitle);
                        BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                        BinaryNode<string, string> * itemPtr = selectedItemTree->returnNode(itemDeleted);
                        auto end = std::chrono::high_resolution_clock::now();
                        timerBST += (end-start).count() / 1000.0;
                        
                        auto start2 = std::chrono::high_resolution_clock::now();
                        AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(choosenTitle);
                        AvlTree<string, string> * selectedItemTreeAvl = sectionsAVL.returnRest(sectionNodePtrAvl);
                        AvlNode<string, string> * itemPtrAvl = selectedItemTreeAvl->returnNode(itemDeleted);
                        auto end2 = std::chrono::high_resolution_clock::now();
                        timerAVL += (end2-start2).count() / 1000.0;
                        
                        
                        if(itemPtr == NULL && itemPtrAvl == NULL){
                            cout << "Item \"" << itemDeleted << "\" does not exist in the \"" << choosenTitle << "\"." << endl;
                            timerBST = 0;
                            timerAVL = 0;
                        }
                        
                        else{
                            
                            auto start = std::chrono::high_resolution_clock::now();
                            selectedItemTree->remove(itemDeleted);
                            auto end = std::chrono::high_resolution_clock::now();
                            timerBST += (end-start).count() / 1000.0;
                            
                            auto start2 = std::chrono::high_resolution_clock::now();
                            selectedItemTreeAvl->remove(itemDeleted);
                            auto end2 = std::chrono::high_resolution_clock::now();
                            timerAVL += (end2-start2).count() / 1000.0;
                            cout << "[AVL] Elapsed time: " << timerAVL << " microseconds" << endl;
                            timerAVL = 0;
                            
                            cout << "[BST] Elapsed time: " << timerBST << " microseconds" << endl;
                            timerBST = 0;
                            cout << "The item \"" << itemDeleted << "\" has been deleted." << endl;
                        }
                    }
                    cout << "\nInput: ";
                    cin >> choice2;
                }
                if (choice2 == 7) {
                    cout << "\n\nMENU\nPlease enter an input between [1 - 6]:\n1- Display the sections [AVL]\n2- Display the sections [BST]\n3- Select a section\n4- Add new section\n5- Delete a section\n6- Exit";
                }
            }
        }
        
        else if (choice==4){
            string insertedTitle;
            cout << "Enter the title for the section: ";
            cin >> insertedTitle;
            
            if(sectionsBST.returnNode(insertedTitle)!=NULL && sectionsAVL.returnNode(insertedTitle)!=NULL){
                cout << "Section \"" << insertedTitle << "\" already exists.\n";
            }
            else{
                BinarySearchTree<string, string> * newPtrItemTree = new BinarySearchTree<string, string>(notFound);
                sectionsBST.insert(insertedTitle, newPtrItemTree);
                
                AvlTree<string, string> * newPtrItemTreeAvl = new AvlTree<string, string>(notFound);
                sectionsAVL.insert(insertedTitle, newPtrItemTreeAvl);
                cout << "The new section \"" << insertedTitle << "\"  has been inserted.\n";
            }
        }
        
        else if (choice==5){
            
            string deletedSection;
            cout << "Enter the title for the section: ";
            cin >> deletedSection;
            BinaryNode<string, BinarySearchTree<string,string>*> * sectionNodePtr = sectionsBST.returnNode(deletedSection);
            AvlNode<string, AvlTree<string,string>*> * sectionNodePtrAvl = sectionsAVL.returnNode(deletedSection);
            
            if(sectionNodePtr==NULL){
                cout << "Section \"" << deletedSection << "\"  does not exist.\n";
            }
            else{
                //BinarySearchTree<string, string> * selectedItemTree = sectionsBST.returnRest(sectionNodePtr);
                sectionsBST.returnRest(sectionNodePtr)->makeEmpty();
                delete sectionsBST.returnRest(sectionNodePtr);
                sectionsBST.remove(deletedSection);
                
                sectionsAVL.returnRest(sectionNodePtrAvl)->makeEmpty();
                delete sectionsAVL.returnRest(sectionNodePtrAvl);
                sectionsAVL.remove(deletedSection);
                
                cout << "The section has been deleted.\n";
            }
            //DO SAME FOR AVL
        }
        cout << "\nInput: ";
        cin >> choice;
    }
    
    return 0;
}
