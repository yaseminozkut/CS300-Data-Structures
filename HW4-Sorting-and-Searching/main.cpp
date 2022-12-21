#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "strutils.h"
using namespace std;

struct ContactInfo{
    string name;
    string surname;
    string phone;
    string city;
    ContactInfo() {}
    ContactInfo(string n, string s, string p, string c): name(n), surname(s), phone(p), city(c) {}
    bool operator<(const ContactInfo& w){
        if(name != w.name)
            return (name < w.name);
        else
            return (surname < w.surname);
    }
    
    bool operator>(const ContactInfo& w){
        if(name != w.name)
            return (name > w.name);
        else
            return (surname > w.surname);
    }
    
    bool operator<=(const ContactInfo& w){
        if(name != w.name)
            return (name <= w.name);
        else
            return (surname <= w.surname);
    }
    
    bool find(string searchedName){
        if (this->name == searchedName){
            return true;
        }
        else
            return false;
    }
    
    bool find(string searchedName, string searchedSurname){
        if (this->name == searchedName && this->surname == searchedSurname){
            return true;
        }
        else
            return false;
    }
};

template <class Comparable>
void insertionSort (vector <Comparable> & a)
{
    int j;
               // loop over the passes
    for (int p = 1;  p < a.size(); p++)
    {
        Comparable tmp = a[p];
                            // loop over the elements
        for (j = p; j > 0 &&  tmp < a[j-1]; j--){
            a[j] = a[j-1];
        }
        a[j] = tmp;
    }
}

template <class Comparable>
inline void swapElements( Comparable & obj1, Comparable & obj2 )
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

inline int leftChild( int i )
{
    return 2*i+1;
}


template <class Comparable>
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;

    for (tmp=a[i] ; leftChild(i) < n; i = child )
    {
         child = leftChild(i);
         if ( child != n-1 && a[ child  ] < a[ child+1 ] )
              child++;
         if ( a[child ] > tmp )
              a[i] = a[ child ];
         else
              break;
    }
    a[ i ] = tmp;
}

template <class Comparable>
void heapsort(vector<Comparable> & a)
{
    // buildHeap
    for (int i = a.size()/2; i >=0; i--)
    {percDown(a, i, a.size());}

    // sort
    for (int j = a.size()-1; j >0; j--)
    {
        swapElements(a[0], a[j]);    // swap max to the last pos.
        percDown(a, 0, j); // re-form the heap
    }
}


template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
  vector<Comparable> tmpArray( a.size( ) );
  mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

template <class Comparable>
void merge(vector<Comparable> & a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd)
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
    // Main loop
    while ( leftPos <= leftEnd && rightPos <= rightEnd )
     if ( a[ leftPos ] <= a[ rightPos ] )
         tmpArray[ tmpPos++ ] = a[ leftPos++ ];
     else
         tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    while ( leftPos <= leftEnd )    // Copy rest of first half
        tmpArray[ tmpPos++ ] = a[ leftPos++ ];

    while ( rightPos <= rightEnd )  // Copy rest of right half
        tmpArray[ tmpPos++ ] = a[ rightPos++ ];

    // Copy tmpArray back
    for ( int i = 0; i < numElements; i++, rightEnd-- )
        a[ rightEnd ] = tmpArray[ rightEnd ];
}

template <class Comparable>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
{
  if ( left < right )
  {
    int center = ( left + right ) / 2;
    mergeSort( a, tmpArray, left, center );
    mergeSort( a, tmpArray, center + 1, right );
    merge( a, tmpArray, left, center + 1, right );
  }
}
        
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ] < a[ left ] )
        swapElements( a[ left ], a[ center ] );
    if ( a[ right ] < a[ left ] )
        swapElements( a[ left ], a[ right ] );
    if ( a[ right ] < a[ center ] )
        swapElements( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    swapElements( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

template <class Comparable>
void internalInsertionSort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;
        for ( j = p; j > left && tmp < a[ j -1 ]; j-- )
           a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
    }
}

template <class Comparable>
void quicksort( vector<Comparable> & a, int left, int right )
{
    if ( left + 10 <= right ){
        Comparable pivot = median3( a, left, right );
        int i = left, j = right - 1;
        for ( ; ; ){
            while ( a[ ++i ] < pivot ) { }

            while ( pivot < a[ --j ] ) { }

            if ( i < j )
                swapElements( a[ i ], a[ j ] );
            else
                  break;
        }
        swapElements( a[ i ], a[ right - 1 ] );   // Restore pivot
        quicksort( a, left, i - 1 );       // Sort small elements
        quicksort( a, i + 1, right );    // Sort large elements
    }
    
    else  // Do an insertion sort on the subarray
        internalInsertionSort( a, left, right );
}

template <class Comparable>
void quicksort( vector<Comparable> & a )
{
    quicksort( a, 0, a.size( ) - 1 );
}

void binarySearch(vector<ContactInfo>& list, vector<string>& key, vector<ContactInfo>& returningList){
    // pre: list.size() == # elements in list
    // post: returns index of key in list, -1 if key not found
    int low = 0; // leftmost possible entry
    int high = list.size()-1; // rightmost possible entry
    int mid; // middle of current range
    
    if(key.size() == 1){
        while (low <= high){
            mid = (low + high)/2;
            if (list[mid].name.find(key[0])!= -1){ // found key, exit search
                ContactInfo tempContact = list[mid];
                returningList.push_back(tempContact);
                
                int currentIdx = mid-1;
                while(list[currentIdx].name.find(key[0])!= -1){
                    ContactInfo tempContact2 = list[currentIdx];
                    returningList.push_back(tempContact2);
                    currentIdx--;
                }
                currentIdx = mid+1;
                while(list[currentIdx].name.find(key[0])!= -1){
                    ContactInfo tempContact3 = list[currentIdx];
                    returningList.push_back(tempContact3);
                    currentIdx++;
                }
                return;
            }
            else if (list[mid].name < key[0]) // key in upper half
                low = mid + 1;
            else // key in lower half
                high = mid - 1;
        }
    }

    else if(key.size() == 2){
        while (low <= high){
            mid = (low + high)/2;
            if (list[mid].name == key[0]){ // found key, exit search
                if(list[mid].surname == key[1]){
                    ContactInfo tempContact = list[mid];
                    returningList.push_back(tempContact);
                    return;
                }
                else if (list[mid].surname < key[1]) // key in upper half
                    low = mid + 1;
                else
                    high = mid - 1;
            }
            else if (list[mid].name < key[0]) // key in upper half
                low = mid + 1;
            else // key in lower half
                high = mid - 1;
        }
    }
}

void sequentialSearch(vector<ContactInfo>& list, vector<string>& key, vector<ContactInfo>& returningList){
    if(key.size() == 1){
        for(int i = 0; i < list.size(); i++){
            if(list[i].name.find(key[0])!=-1){
                ContactInfo tempContact = list[i];
                returningList.push_back(tempContact);
            }
        }
    }
    
    else if(key.size() == 2){
        for(int i = 0; i < list.size(); i++){
            if(list[i].find(key[0], key[1])){
                ContactInfo tempContact = list[i];
                returningList.push_back(tempContact);
            }
        }
    }

}

int main() {
    string fileName;
    cout << "Please enter the contact file name:\n";
    cin >> fileName;
    ifstream is;
    string line;
    is.open(fileName.c_str());
    vector<ContactInfo> contactsVecQuick, contactsVecInsertion, contactsVecMerge, contactsVecHeap;
    while(getline(is, line)){
        ContactInfo tempContact;
        istringstream issInput(line);
        string tempName, tempSurname, tempPhone, tempCity;
        while(issInput >> tempName >> tempSurname >> tempPhone >>tempCity){
            ToUpper(tempName);
            ToUpper(tempSurname);
            tempContact.name = tempName;
            tempContact.surname = tempSurname;
            tempContact.phone = tempPhone;
            tempContact.city = tempCity;
            contactsVecQuick.push_back(tempContact);
            contactsVecInsertion.push_back(tempContact);
            contactsVecMerge.push_back(tempContact);
            contactsVecHeap.push_back(tempContact);
        }
    }
    string input;
    cout << "Please enter the word to be queried :\n";
    cin.get();
    getline(cin, input);
    istringstream queryInput(input);
    string tempWord, tempWord2;
    vector<string> queriedName, queriedName2;
    while(queryInput>>tempWord){
        tempWord2 = tempWord;
        queriedName2.push_back(tempWord2);
        ToUpper(tempWord);
        queriedName.push_back(tempWord);
    }
    
    cout << "Sorting the vector copies\n======================================\n";
    
    const int N = 100;
    auto startQuickSort = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempVec = contactsVecQuick;
        quicksort(tempVec);
    }
    auto quickSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startQuickSort);
    cout << "Quick Sort Time: " << quickSortTime.count() / N << " Nanoseconds\n";
    quicksort(contactsVecQuick);
    
    auto startInsSort = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempVec = contactsVecInsertion;
        insertionSort(tempVec);
    }
    auto insSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startInsSort);
    cout << "Insertion Sort Time: " << insSortTime.count() / N << " Nanoseconds\n";
    insertionSort(contactsVecInsertion);
    
    auto startMergeSort = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempVec = contactsVecMerge;
        mergeSort(tempVec);
    }
    auto mergeSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startMergeSort);
    cout << "Merge Sort Time: " << mergeSortTime.count() / N  << " Nanoseconds\n";
    mergeSort(contactsVecMerge);
    
    auto startHeapSort = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempVec = contactsVecHeap;
        heapsort(tempVec);
    }
    auto heapSortTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startHeapSort);
    cout << "Heap Sort Time: " << heapSortTime.count() / N << " Nanoseconds\n";
    heapsort(contactsVecHeap);
    
    vector<ContactInfo> namesSequentialList;
    vector<ContactInfo> namesBinaryList;

    if(queriedName.size() == 1){
        cout << "\nSearching for " << queriedName2[0] << "\n======================================\n";
    }
    else if(queriedName.size() == 2){
        cout << "\nSearching for " << queriedName2[0] << " " << queriedName2[1] << "\n======================================\n";
    }
    
    auto startBinSearch = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempNamesListBinary;
        binarySearch(contactsVecInsertion, queriedName, tempNamesListBinary);
    }
    auto binSearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startBinSearch);
    binarySearch(contactsVecInsertion, queriedName, namesBinaryList);
    quicksort(namesBinaryList);
    namesBinaryList;
    if(namesBinaryList.size() == 0){
        if(queriedName.size() == 1){
        cout << queriedName[0] << " does NOT exist in the dataset\n";
        }
        else if (queriedName.size() == 2){
            cout << queriedName[0] << " " <<  queriedName[1] << " does NOT exist in the dataset\n";
        }
    }
    else{
        for(int i= 0; i<namesBinaryList.size(); i++){
            cout << namesBinaryList[i].name << " " << namesBinaryList[i].surname << " " << namesBinaryList[i].phone << " " << namesBinaryList[i].city << "\n";
        }
    }
    cout << "Binary Search Time: " << (double)binSearchTime.count() / N  << " Nanoseconds\n\n";
    
    
    cout << "Search results for Sequential Search:\n";
    auto startSeqSearch = std::chrono::high_resolution_clock::now(); // start measuring
    for (int i = 0; i < N; i++){
        vector<ContactInfo> tempNamesList;
        sequentialSearch(contactsVecInsertion, queriedName, tempNamesList);
    }
    auto seqSearchTime = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startSeqSearch);
    sequentialSearch(contactsVecInsertion, queriedName, namesSequentialList);
    
    if(namesSequentialList.size() == 0){
        if(queriedName.size() == 1){
        cout << queriedName[0] << " does NOT exist in the dataset\n";
        }
        else if (queriedName.size() == 2){
            cout << queriedName[0] << " " <<  queriedName[1] << " does NOT exist in the dataset\n";
        }
    }
    else{
        for(int i= 0; i<namesSequentialList.size(); i++){
            cout << namesSequentialList[i].name << " " << namesSequentialList[i].surname << " " << namesSequentialList[i].phone << " " << namesSequentialList[i].city << "\n";
        }
    }
    cout << "Sequential Search Time: " << (double)seqSearchTime.count() / N  << " Nanoseconds\n\n";
    
    cout << "SpeedUp between Search Algorithms\n======================================\n";
    cout << "(Sequential Search/ Binary Search) SpeedUp = " << (double)seqSearchTime.count()/binSearchTime.count() << "\n\n";
    
    cout << "SpeedUp between Sorting Algorithms\n======================================\n";
    cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << (double)insSortTime.count()/quickSortTime.count() << "\n";
    cout << "(Merge Sort / Quick Sort) SpeedUp = " << (double)mergeSortTime.count()/quickSortTime.count() << "\n";
    cout << "(Heap Sort / Quick Sort) SpeedUp = " << (double)heapSortTime.count()/quickSortTime.count() << "\n";
    
    
    return 0;
}
