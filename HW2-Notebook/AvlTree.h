#ifndef AvlTree_h
#define AvlTree_h

template <class Comparable, class Rest>
class AvlTree;

template <class Comparable, class Rest>
class AvlNode
{
private:
    Comparable element;
    Rest rest;
    AvlNode *left;
    AvlNode *right;
    int height;
    
    AvlNode( const Comparable theElement, const Rest theRest, AvlNode *lt, AvlNode *rt, int h = 0)
        : element( theElement ), rest(theRest), left( lt ), right( rt ), height(h) { }

    friend class AvlTree<Comparable, Rest>;
};

template <class Comparable, class Rest>
class AvlTree
{
public:
    explicit AvlTree( const Comparable & notFound );
    AvlTree( const AvlTree & rhs );
    ~AvlTree( );

    
    AvlNode<Comparable, Rest> * findNode(const Comparable &) const;

    const Comparable & findMin() const;
    const Comparable & findMax() const;
    const Comparable & find( const Comparable & x) const;
    bool isEmpty( ) const;
    void printTree( ) const;
    
    AvlNode<Comparable, Rest> * returnNode(const Comparable) const;
    const Rest returnRest(AvlNode<Comparable, Rest> *) const;
    
    void makeEmpty( );
    void insert( const Comparable & x, const Rest &);
    void remove( const Comparable & x );
    void updateItemRest(AvlNode<Comparable, Rest>* x, const Rest);
    const AvlTree & operator=( const AvlTree & rhs );
private:
    AvlNode<Comparable, Rest> *root;
    const Comparable ITEM_NOT_FOUND;

    const Comparable & elementAt( AvlNode<Comparable, Rest> *t ) const;

    void insert( const Comparable & x, const Rest & rest, AvlNode<Comparable, Rest> * & t ) const;
    void remove(const Comparable & x, AvlNode<Comparable, Rest> * & t ) const;

    AvlNode<Comparable, Rest> * findMin( AvlNode<Comparable, Rest> *t ) const;
    AvlNode<Comparable, Rest> * findMax( AvlNode<Comparable, Rest> *t ) const;
    AvlNode<Comparable, Rest> * find( const Comparable & x, AvlNode<Comparable, Rest> *t )
        const;
    void makeEmpty( AvlNode<Comparable, Rest> * & t ) const;
    void printTree( AvlNode<Comparable, Rest> *t ) const;
    AvlNode<Comparable, Rest> * clone( AvlNode<Comparable, Rest> *t ) const;

    // Avl manipulations
    int height( AvlNode<Comparable, Rest> *t ) const;
    int max( int lhs, int rhs ) const;
    void rotateWithLeftChild( AvlNode<Comparable, Rest> * & k2 ) const;
    void rotateWithRightChild( AvlNode<Comparable, Rest> * & k1 ) const;
    void doubleWithLeftChild( AvlNode<Comparable, Rest> * & k3 ) const;
    void doubleWithRightChild( AvlNode<Comparable, Rest> * &) const;
};

#endif /* AvlTree_h */
