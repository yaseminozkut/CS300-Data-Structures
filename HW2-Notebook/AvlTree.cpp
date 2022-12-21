
#include "AvlTree.h"
#include <string>
#include <iostream>
using namespace std;

template <class Comparable, class Rest>
int AvlTree<Comparable, Rest>::height( AvlNode<Comparable, Rest> *t )
    const
{
    if (t == nullptr)
        return -1;
    return t->height;
}

template <class Comparable, class Rest>
int AvlTree<Comparable, Rest>::max( int lhs, int rhs )
    const
{
    if (lhs > rhs)
        return lhs;

    return rhs;
}


template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::insert( const Comparable & x , const Rest &rest)
{
    insert( x, rest, root );
}

template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::insert
    ( const Comparable & x, const Rest & rest, AvlNode<Comparable, Rest> * & t ) const
{
    if ( t == NULL )
        t = new AvlNode<Comparable, Rest>( x, rest, NULL, NULL );

    else if ( x < t->element ) {
        // X should be inserted to the left tree!
        insert( x, rest, t->left );
        // Check if the left tree is out of balance (left subtree grew in height!)
        if ( height( t->left ) - height( t->right ) == 2 ){
            if ( x < t->left->element )  // X was inserted to the left-left subtree!
                rotateWithLeftChild( t );
            else                 // X was inserted to the left-right subtree!
                doubleWithLeftChild( t );
        }
    }
    else if( t->element < x )
    {    // Otherwise X is inserted to the right subtree
        insert( x, rest, t->right );
        if ( height( t->right ) - height( t->left ) == 2 ){
            // height of the right subtree increased
                if ( t->right->element < x )
                    // X was inserted to right-right subtree
                        rotateWithRightChild( t );
                else // X was inserted to right-left subtree
                    doubleWithRightChild( t );
        }
    }
    else
        ;  // Duplicate; do nothing

    // update the height the node
    t->height = max( height( t->left ), height( t->right ) ) + 1;
}

/**
* Rotate binary tree node with left child.
* For AVL trees, this is a single rotation for case 1.
* Update heights, then set new root.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::rotateWithLeftChild(
    AvlNode<Comparable, Rest> * & k2 ) const
{
    AvlNode<Comparable, Rest> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::rotateWithRightChild
    ( AvlNode<Comparable, Rest> * & k1 ) const
{
    AvlNode<Comparable, Rest> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}


/**
* Double rotate binary tree node: first left child.
* with its right child; then node k3 with new left child.
* For AVL trees, this is a double rotation for case 2.
* Update heights, then set new root.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::doubleWithLeftChild
    ( AvlNode<Comparable, Rest> * & k3 ) const
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::doubleWithRightChild
    ( AvlNode<Comparable, Rest> * & k1 ) const
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}

/**
* Construct the tree.
*/
template <class Comparable, class Rest>
AvlTree<Comparable , Rest>::
    AvlTree(const Comparable & notFound ) :
    ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable, class Rest>
const Comparable & AvlTree<Comparable, Rest>::
    elementAt( AvlNode<Comparable, Rest> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable, class Rest>
const Comparable & AvlTree<Comparable, Rest>::
    find( const Comparable & x ) const
{
    return elementAt( find( x, root ) );
}


/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable, class Rest>
AvlNode<Comparable, Rest> *
    AvlTree<Comparable, Rest>::
    find( const Comparable & x, AvlNode<Comparable, Rest> * t ) const
{
    if ( t == NULL )
        return NULL;
    else if( x < t->element )
        return find( x, t->left );
    else if( t->element < x )
        return find( x, t->right );
    else
        return t;    // Match
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable, class Rest>
const Comparable & AvlTree<Comparable, Rest>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable, class Rest>
AvlNode<Comparable, Rest> *
    AvlTree<Comparable, Rest>::findMin( AvlNode<Comparable, Rest> *t )
    const
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable, class Rest>
AvlNode<Comparable, Rest> *
    AvlTree<Comparable, Rest>::findMax( AvlNode<Comparable, Rest> *t )
    const
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable, class Rest>
const Comparable & AvlTree<Comparable, Rest>::findMax() const
{
    return elementAt(findMax(root));
}
         

/**
* Make the tree logically empty.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::makeEmpty( )
{
    makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::
    makeEmpty( AvlNode<Comparable, Rest> * & t ) const
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

/**
* Print the tree contents in sorted order.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::printTree( ) const
{
    if( isEmpty( ) )
        cout << "" << endl;
    else
        printTree( root );
}

template <class Comparable, class Rest>
bool AvlTree<Comparable, Rest>::isEmpty( ) const {
    if(root == NULL)
        return true;
    return false;
}

/**
* Destructor for the tree.
*/
template <class Comparable, class Rest>
AvlTree<Comparable, Rest>::~AvlTree( )
{
    makeEmpty( );
}

/**
* Copy constructor.
*/
template <class Comparable, class Rest>
AvlTree<Comparable, Rest>::
    AvlTree( const AvlTree<Comparable, Rest> & rhs ) :
    root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::
    printTree( AvlNode<Comparable, Rest> * t ) const
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}

/**
* Internal method to clone subtree.
*/
template <class Comparable, class Rest>
AvlNode<Comparable, Rest> *
    AvlTree<Comparable, Rest>::
    clone( AvlNode<Comparable, Rest> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new AvlNode<Comparable, Rest>
        ( t->element,
        clone( t->left ),
        clone( t->right ) );
}

template <class Comparable, class Rest>
AvlNode<Comparable, Rest> * AvlTree<Comparable, Rest>::returnNode( const Comparable x) const {
    
    AvlNode<Comparable, Rest> * t = root;
    while( t != NULL ){
        if( x < t->element )
            t = t->left;
        else if( t->element < x )
            t = t->right;
        else
            return t;    //
    }
    return NULL;   // No match
}

template <class Comparable, class Rest>
const Rest AvlTree<Comparable, Rest>::returnRest(AvlNode<Comparable, Rest> * nodePtr) const{
    return nodePtr->rest;
}


template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::updateItemRest(AvlNode<Comparable, Rest> * x, const Rest updatedRest){
    x->rest = updatedRest;
}



template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::remove( const Comparable & x )
{
    remove( x, root );
}



template <class Comparable, class Rest>
void AvlTree<Comparable, Rest>::remove(const Comparable & x, AvlNode<Comparable, Rest> * & t ) const
{

    if (t == NULL)
        return;
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->rest = findMin( t->right )->rest;
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        AvlNode<Comparable, Rest> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
        return;
    }
    

    t->height = max( height( t->left ), height( t->right ) ) + 1;
    
    

    if ( height( t->left ) - height( t->right ) > 1 ){
        if ( height( t->left->left ) - height( t->left->right ) >= 0 )  // X was inserted to the left-left subtree!
            rotateWithLeftChild( t );
        else                 // X was inserted to the left-right subtree!
            doubleWithLeftChild( t );
    }
    
    else if ( height( t->right ) - height( t->left ) > 1 ){
        // height of the right subtree increased
            if ( height( t->right->right ) - height( t->right->left ) >= 0 )
                // X was inserted to right-right subtree
                    rotateWithRightChild( t );
            else // X was inserted to right-left subtree
                doubleWithRightChild( t );
    }
    
    else;
    
}

