#include "BinarySearchTree.h"

/**
* Construct the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(Comparable & notFound )
    :ITEM_NOT_FOUND( notFound ), root( NULL )
{
}

/**
* Internal method to get element field in node t.
* Return the element field or ITEM_NOT_FOUND if t is NULL.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::elementAt( BinaryNode<Comparable> *t ) const
{
    return t == NULL ? ITEM_NOT_FOUND : t->element;
}

/**
* Find item x in the tree.
* Return the matching item or ITEM_NOT_FOUND if not found.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::find( Comparable & x ) const
{
    return elementAt( find( x, root ) );
}


/**
* Internal method to find an item in a subtree.
* x is item to search for.
* t is the node that roots the tree.
* Return node containing the matched item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find(Comparable & x, BinaryNode<Comparable> * t ) const
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

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::returnNode( Comparable x) const {
    
    BinaryNode<Comparable> * t = root;
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



template <class Comparable>
Comparable * BinarySearchTree<Comparable>::returnElement(BinaryNode<Comparable> * nodePtr) const{
    
    Comparable * ptr = &(nodePtr->element);
    
    return ptr;
    
}

/**
* Find the smallest item in the tree.
* Return smallest item or ITEM_NOT_FOUND if empty.
*/
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

/**
* Internal method to find the smallest item in a subtree t.
* Return node containing the smallest item.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> *t ) const
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
template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const
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
template <class Comparable>
Comparable & BinarySearchTree<Comparable>::findMax() const
{
    return elementAt(findMax(root));
}

/**
* Insert x into the tree; duplicates are ignored.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert(Comparable & x)
{
    insert( x, root );
}

/**
* Internal method to insert into a subtree.
* x is the item to insert.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::insert(Comparable & x, BinaryNode<Comparable> * &t )
{
    BinaryNode<Comparable> * tempRoot = t;
    BinaryNode<Comparable> * parent = NULL;
    BinaryNode<Comparable> * temp = new BinaryNode<Comparable>( x, NULL, NULL );
    
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
template <class Comparable>
void BinarySearchTree<Comparable>::remove
    ( Comparable & x )
{
    remove( x, root );
}

/**
* Internal method to remove from a subtree.
* x is the item to remove.
* t is the node that roots the tree.
* Set the new root.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::remove( Comparable & x, BinaryNode<Comparable> * & t ) const
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
    else if( t->left != NULL && t->right != NULL ) // Two children
    {
        t->element = findMin( t->right )->element;
        remove( t->element, t->right );
    }
    else // one or no children
    {
        BinaryNode<Comparable> *oldNode = t;
        t = ( t->left != NULL ) ? t->left : t->right;
        delete oldNode;
    }
}

/**
* Make the tree logically empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

/**
* Internal method to make subtree empty.
*/
template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const
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
template <class Comparable>
int BinarySearchTree<Comparable>::countNode( ) const
{
    if( isEmpty( ) )
        return 0;
    else
        return countNode( root );
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty( ) const {
    if(root == NULL)
        return true;
    return false;
}

/**
* Destructor for the tree.
*/
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty();
}

/**
* Copy constructor.
*/
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs )
    : root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{
    *this = rhs;
}

/**
* Internal method to print a subtree rooted at t in sorted order.
*/
template <class Comparable>
int BinarySearchTree<Comparable>::countNode( BinaryNode<Comparable> * t ) const
{
    
    if ( t != NULL )
    {
        return 1 + countNode(t->left)+countNode(t->right);
    }
    else
        return 0;
}

/**
* Internal method to clone subtree.
*/
template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const
{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable>
        ( t->element,
        clone( t->left ),
        clone( t->right ) );
}

