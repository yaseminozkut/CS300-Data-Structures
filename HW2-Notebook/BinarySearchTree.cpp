
#include "BinarySearchTree.h"

/**
* Construct the tree.
*/
template <class Comparable, class Rest>
BinarySearchTree<Comparable, Rest>::BinarySearchTree(const Comparable & notFound )
    :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable, class Rest>
const Comparable & BinarySearchTree<Comparable, Rest>::elementAt( BinaryNode<Comparable, Rest> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable, class Rest>
const Comparable & BinarySearchTree<Comparable, Rest>::find( const Comparable & x ) const
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
BinaryNode<Comparable, Rest> * BinarySearchTree<Comparable, Rest>::find( const Comparable & x, BinaryNode<Comparable, Rest> * t ) const
{
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
BinaryNode<Comparable, Rest> * BinarySearchTree<Comparable, Rest>::returnNode( const Comparable x) const {
    
    BinaryNode<Comparable, Rest> * t = root;
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
const Rest BinarySearchTree<Comparable, Rest>::returnRest(BinaryNode<Comparable, Rest> * nodePtr) const{
    return nodePtr->rest;
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable, class Rest>
const Comparable & BinarySearchTree<Comparable, Rest>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable, class Rest>
BinaryNode<Comparable, Rest> * BinarySearchTree<Comparable, Rest>::findMin(BinaryNode<Comparable, Rest> *t ) const
{
    if( t != NULL )
        while( t->left != NULL )
            t = t->left;
    return t;
}

/**
* Internal method to find the largest item in a subtree t.
* Return node containing the largest item.
*/
template <class Comparable, class Rest>
BinaryNode<Comparable, Rest> *BinarySearchTree<Comparable, Rest>::findMax( BinaryNode<Comparable, Rest> *t ) const
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
const Comparable & BinarySearchTree<Comparable, Rest>::findMax() const
{
    return elementAt(findMax(root));
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::insert( const Comparable & x , const Rest &rest)
{
    insert( x, rest, root );
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::insert( const Comparable & x, const Rest & rest, BinaryNode<Comparable, Rest> * &t )
{
    BinaryNode<Comparable, Rest> * tempRoot = t;
    BinaryNode<Comparable, Rest> * parent = NULL;
    BinaryNode<Comparable, Rest> * temp = new BinaryNode<Comparable, Rest>( x, rest, NULL, NULL );
    
    if(tempRoot!=NULL){
        while(tempRoot != NULL){
            parent = tempRoot;
            if( x < tempRoot->element )
                tempRoot = tempRoot->left;
            else if( tempRoot->element < x )
                tempRoot = tempRoot->right;
            else
                return;
        }
        if(x< parent->element){
            parent->left = temp;
        }
        else if (parent->element < x){
            parent->right = temp;
        }
        else
            return;
    }
    else{
        t = temp;
    }
    
}

/**
* Remove x from the tree. Nothing is done if x is not found.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::remove
    ( const Comparable & x )
{
    remove( x, root );
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::remove( const Comparable & x, BinaryNode<Comparable, Rest> * & t ) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
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
        BinaryNode<Comparable, Rest> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

/**
* Make the tree logically empty.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::makeEmpty( )
{
    makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::makeEmpty( BinaryNode<Comparable, Rest> * & t ) const
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
void BinarySearchTree<Comparable, Rest>::printTree( ) const
{
    if( isEmpty( ) )
        cout << "" << endl;
    else
        printTree( root );
}

template <class Comparable, class Rest>
bool BinarySearchTree<Comparable, Rest>::isEmpty( ) const {
    if(root == NULL)
        return true;
    return false;
}

/**
* Destructor for the tree.
*/
template <class Comparable, class Rest>
BinarySearchTree<Comparable, Rest>::~BinarySearchTree( )
{
    makeEmpty();
}

/**
* Copy constructor.
*/
template <class Comparable, class Rest>
BinarySearchTree<Comparable, Rest>::BinarySearchTree( const BinarySearchTree<Comparable, Rest> & rhs )
    : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::printTree( BinaryNode<Comparable, Rest> * t ) const
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
BinaryNode<Comparable, Rest> * BinarySearchTree<Comparable, Rest>::clone( BinaryNode<Comparable, Rest> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable, Rest>
        ( t->element,
        clone( t->left ),
        clone( t->right ) );
}

template <class Comparable, class Rest>
void BinarySearchTree<Comparable, Rest>::updateItemRest(BinaryNode<Comparable, Rest> * x, const Rest updatedRest){
    x->rest = updatedRest;
}
