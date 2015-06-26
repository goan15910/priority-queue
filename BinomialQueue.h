#ifndef BINOMIAL_QUEUE_H
#define BINOMIAL_QUEUE_H

#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename Comparable>
class BinomailQueue
{
  public:
    BinomialQueue();
    ~BinomialQueue();
    bool isEmpty() const;
    void insert( const Comparable & x );
    void deleteMin();
    void free( Node* );
    void merge( BinomialQueue &rhs );

  private:
    struct Node
    {
      Comparable element;
      Node* left;
      Node* next;

      Node( const Comparable & e, Node* lt, Node* rt )
        : element(e), left(lt), next(rt)
      {
        //empty body
      }
    }

    vector<Node*> roots;
    int currentSize;

    void makeEmpty( Node* &t );
};

template <typename Comparable>
BinomialQueue<Comparable>::BinomialQueue()
  : roots(1), currentSize(0)
{
  roots[0] = NULL;
}

template <typename Comparable>
BinomialQueue<Comparable>::~BinomialQueue()
{
  for(int i = 0; i < roots.size(); i++)
    free(roots[i]);
}

template <typename Comparable>
bool BinomialQueue<Comparable>::isEmpty() const
{
  return (currentSize == 0);
}

template <typename Comparable>
void BinomialQueue<Comparable>::insert( const Comparable & x )
{
//TODO
}

template <typename Comparable>
void BinomialQueue<Comparable>::deleteMin()
{
//TODO
}

template <typename Comparable>
void BinomialQueue<Comparable>::free( Node* node )
{
  if( node->left != NULL )
    free(node-left);
  if( node->next != NULL )
    free(node->next);
  delete node;
}

template <typename Comparable>
void BinomialQueue<Comparable>::merge( BinomialQueue &rhs )
{
//TODO
}


#endif
