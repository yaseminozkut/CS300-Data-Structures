//Code given by Sabancı University

#ifndef DynTemplatedStack_h
#define DynTemplatedStack_h
#include <iostream>
using namespace std;


template <class Object>
class Stack {
public:
    Stack( );
    ~Stack( );

    bool isEmpty() const;
    bool isFull() const;
    void makeEmpty();

    void pop();
    void push(const Object & x);
    Object topAndPop();
    const Object & top() const;

private:
    struct ListNode
    {
      Object element;
      ListNode *next;

      ListNode(const Object & theElement, ListNode * n = NULL)
          : element(theElement), next(n) {}
    };
    
    ListNode *topOfStack; 
};
#endif /* DynTemplatedStack_h */

