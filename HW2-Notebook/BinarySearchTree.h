
#ifndef BinarySearchTree_h
#define BinarySearchTree_h
#include <iostream>
using namespace std;


template <class Comparable, class Rest>
//template <class Comparable>
class BinarySearchTree;

template <class Comparable, class Rest>
//template <class Comparable>
class BinaryNode
{
private:
    Comparable element;
    Rest rest;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode( const Comparable theElement, const Rest theRest,
        BinaryNode *lt, BinaryNode *rt)
        : element( theElement ), rest(theRest), left( lt ), right( rt ){ }

    friend class BinarySearchTree<Comparable, Rest>;
};


template <class Comparable, class Rest>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(const Comparable &);
    BinarySearchTree(const BinarySearchTree &);
    ~BinarySearchTree();

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    const Comparable & find( const Comparable &) const;
    bool isEmpty() const;
    void printTree() const;
    BinaryNode<Comparable, Rest> * returnNode( const Comparable) const;
    const Rest returnRest(BinaryNode<Comparable, Rest> *) const;

    void makeEmpty( );
    void insert( const Comparable &, const Rest &);
    void remove( const Comparable &);
    void updateItemRest(BinaryNode<Comparable, Rest> * x, const Rest);

    const BinarySearchTree & operator=( const BinarySearchTree &);
private:
    BinaryNode<Comparable, Rest> *root;
    const Comparable ITEM_NOT_FOUND; //

    const Comparable & elementAt( BinaryNode<Comparable, Rest> *t) const;

    void insert( const Comparable &x, const Rest & rest, BinaryNode<Comparable, Rest> * &t);
    void remove( const Comparable &x, BinaryNode<Comparable, Rest> * &t) const;
    BinaryNode<Comparable, Rest> * findMin( BinaryNode<Comparable, Rest> *t) const;
    BinaryNode<Comparable, Rest> * findMax( BinaryNode<Comparable, Rest> *t) const;
    BinaryNode<Comparable, Rest> * find( const Comparable &x, BinaryNode<Comparable, Rest> *t) const;
    void makeEmpty( BinaryNode<Comparable, Rest> * &t) const;
    void printTree( BinaryNode<Comparable, Rest> *t) const;
    BinaryNode<Comparable, Rest> * clone( BinaryNode<Comparable, Rest> *t) const;
};

#endif /* BinarySearchTree_h */
