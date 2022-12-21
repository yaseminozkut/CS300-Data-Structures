
#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include <iostream>
using namespace std;


template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
private:
    Comparable element;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode(Comparable theElement, BinaryNode *lt, BinaryNode *rt)
        : element( theElement ), left( lt ), right( rt ){ }

    friend class BinarySearchTree<Comparable>;
};


template <class Comparable>
class BinarySearchTree
{
public:
    BinarySearchTree(Comparable &);
    BinarySearchTree(const BinarySearchTree &);
    ~BinarySearchTree();

    Comparable & findMin() const;
    Comparable & findMax() const;
    Comparable & find( Comparable &) const;
    bool isEmpty() const;
    int countNode() const;
    BinaryNode<Comparable> * returnNode(Comparable) const;
    Comparable * returnElement( BinaryNode<Comparable> *) const;

    void makeEmpty( );
    void insert(Comparable &);
    void remove(Comparable &);
    void updateItemRest(BinaryNode<Comparable> * x);

    const BinarySearchTree & operator=( const BinarySearchTree &);
private:
    BinaryNode<Comparable> *root;
    Comparable ITEM_NOT_FOUND; //

    Comparable & elementAt( BinaryNode<Comparable> *t) const;

    void insert( Comparable &x, BinaryNode<Comparable> * &t);
    void remove( Comparable &x, BinaryNode<Comparable> * &t) const;
    BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> * find( Comparable &x, BinaryNode<Comparable> *t) const;
    void makeEmpty( BinaryNode<Comparable> * &t) const;
    int countNode( BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t) const;
};

#endif /* BinarySearchTree_h */
