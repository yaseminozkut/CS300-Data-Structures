//#include "HashTable.h"

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


template <class Type>
int hash( Type & key, int tableSize)
{
    int hashVal = 0;
  
    for (int i = 0; i < key.length(); i++)
      hashVal = 37 * hashVal + key[ i ];

    hashVal = hashVal % tableSize;

    if (hashVal < 0)
      hashVal = hashVal + tableSize;

   return(hashVal);
}




/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound,
                                      int size )
          : ITEM_NOT_FOUND( notFound ), hashArr( nextPrime( size ) )
{
       makeEmpty( );
}
/*
template <class HashedObj>
int HashTable<HashedObj>::hashMain( HashedObj & x ){
    return hash(x, hashArr.size());
}
*/
/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const
{
    
    int collisionNum = 0;
    
    int hashVal = 0;
    for (int i = 0; i < x.length(); i++)
      hashVal = 37 * hashVal + x[ i ];

    hashVal = hashVal % hashArr.size();

    if (hashVal < 0)
      hashVal = hashVal + hashArr.size();
    int currentPos = hashVal;
    //int currentPos = hashMain(x);
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
 bool HashTable<HashedObj>::isActive( int currentPos ) const
 {
       return hashArr[ currentPos ].info == ACTIVE;
 }


/**
 * Remove item x from the hash table.
 *  x has to be in the table
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
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
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x ) const
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
 void HashTable<HashedObj>::insert( const HashedObj & x )
 {
      // Insert x as active
      int currentPos = findPos( x );
      if ( isActive( currentPos ) )
           return;
     hashArr[ currentPos ] = HashEntry( x, ACTIVE );

      // enlarge the hash table if necessary
    if ( ++currentSize >= hashArr.size( ) / 2 )
         rehash( );
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

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
             insert( oldArray[ i ].element );
}

/**
  * Make the hash table logically empty.
  */
 template <class HashedObj>
 void HashTable<HashedObj>::makeEmpty( )
 {
     currentSize = 0;
 }
