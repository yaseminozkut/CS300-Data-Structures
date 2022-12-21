#ifndef HashTable_h
#define HashTable_h
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;
double loadFactor = 0.60;
struct DocumentItem{
    string documentName;
    int count;
    DocumentItem(string d, int c): documentName(d), count(c) {}
};

struct WordItem{
    string word;
    vector<DocumentItem> listDocItem;
    
    bool operator<(const WordItem& w){
        return (word < w.word);
    }
    
    bool operator>(const WordItem& w){
        return (word > w.word);
    }
    
    bool operator==(const WordItem& w){
        return (word == w.word);
    }
    
    bool operator!=(const WordItem& w){
        return (word != w.word);
    }
    WordItem(){}
    
    WordItem(string w){
        word = w;
    }
    
    WordItem(string w, string d){
        word = w;
        listDocItem.push_back(DocumentItem(d, 1));
    }
    int length(){
        return word.length();
    }
};


template <class HashedObj>
class HashTable
{
  public:
    explicit HashTable( HashedObj & notFound, int size = 50);
    HashTable( const HashTable & rhs )
           : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), hashArr( rhs.hashArr ), currentSize( rhs.currentSize ) { }

    HashedObj & find( HashedObj & x );
    int findPos( HashedObj & x );
    void makeEmpty( );
    void insert( HashedObj & x );
    void remove( HashedObj & x );
    int hashMain(HashedObj & x );
    const HashTable & operator=( const HashTable & rhs );
    int returnCurrSize();
    int returnTableSize();
    enum EntryType { ACTIVE, EMPTY, DELETED };
    
    /**
     * Internal method to test if a positive number is prime.
     * Not an efficient algorithm.
     */
    bool isPrime( int n )
    {
        if ( n == 2 || n == 3 )
            return true;

        if ( n == 1 || n % 2 == 0 )
            return false;

        for ( int i = 3; i * i <= n; i += 2 )
             if ( n % i == 0 )
                 return false;

        return true;
    }

    /**
    * Internal method to return a prime number
    * at least as large as n.  Assumes n > 0.
    */
    int nextPrime( int n )
    {
         if ( n % 2 == 0 )
             n++;

         for ( ; ! isPrime( n ); n += 2 )
              ;

         return n;
    }



    int hash( WordItem & key, int tableSize)
    {
        int hashVal = 0;
      
        for (int i = 0; i < key.word.length(); i++)
          hashVal = 37 * hashVal + key.word[ i ];

        hashVal = hashVal % tableSize;

        if (hashVal < 0)
          hashVal = hashVal + tableSize;

       return(hashVal);
    }

private:
    struct HashEntry
    {
         HashedObj element;
         EntryType info;

         HashEntry( const HashedObj & e = HashedObj( ),
                    EntryType i = EMPTY )
                  : element( e ), info( i ) { }
    };
            
    vector<HashEntry> hashArr;
    int currentSize;
    HashedObj ITEM_NOT_FOUND;

    bool isActive( int currentPos );
    void rehash( );
 };


/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( HashedObj & notFound,
                                      int size )
          : ITEM_NOT_FOUND( notFound ), hashArr( nextPrime( size ) )
{
       makeEmpty( );
}

template <class HashedObj>
int HashTable<HashedObj>::hashMain( HashedObj & x ){
    return hash(x, hashArr.size());
}

/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos( HashedObj & x )
{
    
    int collisionNum = 0;

    int currentPos = hashMain(x);
    while ( hashArr[ currentPos ].info != EMPTY &&
          hashArr[ currentPos ].element != x )
    {
        currentPos += pow(++collisionNum, 2) ;  //add the difference
        if ( currentPos >= hashArr.size( ) )              // perform the mod
             currentPos = currentPos - hashArr.size( );                // if necessary
    }
    return currentPos;
}

/**
  * Return true if currentPos exists and is active.
  */
 template <class HashedObj>
 bool HashTable<HashedObj>::isActive( int currentPos )
 {
       return hashArr[ currentPos ].info == ACTIVE;
 }


/**
 * Remove item x from the hash table.
 *  x has to be in the table
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( HashedObj & x )
{
      int currentPos = findPos( x );
      if ( isActive( currentPos ) )
          hashArr[ currentPos ].info = DELETED;
}

/**
 * Find item x in the hash table.
 * Return the matching item, or ITEM_NOT_FOUND, if not found.
 */
template <class HashedObj>
HashedObj & HashTable<HashedObj>::find( HashedObj & x )
{
     int currentPos = findPos( x );
     if (isActive( currentPos ))
          return hashArr[ currentPos ].element;

     return   ITEM_NOT_FOUND;
}

/**
  * Insert item x into the hash table. If the item is
  * already present, then do nothing.
  */
 template <class HashedObj>
 void HashTable<HashedObj>::insert( HashedObj & x )
 {
    // Insert x as active
    int prevTableSize = hashArr.size();
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
       return;
    hashArr[ currentPos ] = HashEntry( x, ACTIVE );
    // enlarge the hash table if necessary
     if ( ++currentSize >= hashArr.size( ) * loadFactor ){
         rehash( );
         cout << "rehashed..." << endl;
         cout << "previous table size: " << prevTableSize << ", new table size: " << hashArr.size() << ", current unique word count " << currentSize << ", current load factor: " << double(currentSize)/hashArr.size() << endl;
     }
 }

/**
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
    vector<HashEntry> oldArray = hashArr;

    // Create new double-sized, empty table
    hashArr.resize( nextPrime( 2 * oldArray.size()));
    for ( int j = 0; j < hashArr.size( ); j++ )
        hashArr[ j ].info = EMPTY;
    
    vector<HashEntry> newArray = hashArr;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE ){
            //newArray[ i ].info = ACTIVE;
            insert( oldArray[ i ].element );
        }
    
    //hashArr = newArray;
}

/**
  * Make the hash table logically empty.
  */
 template <class HashedObj>
 void HashTable<HashedObj>::makeEmpty( )
 {
     currentSize = 0;
 }


template <class HashedObj>
int HashTable<HashedObj>::returnCurrSize(){
    return currentSize;
}


template <class HashedObj>
int HashTable<HashedObj>::returnTableSize(){
    return hashArr.size();
}

#endif

