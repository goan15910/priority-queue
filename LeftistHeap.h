#ifndef LEFTIST_HEAP_H
#define LEFTIST_HEAP_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Comparable>
class LeftistHeap
{
  public:
    LeftistHeap();
    ~LeftistHeap();
    bool isEmpty() const;
    void insert( const Comparable & x );
    void deleteMin( Comparable & minItem );
    void makeEmpty();
    void merge( LeftistHeap & rhs );
  private:
    struct Node
    {
      Comparable element;
      Node* left;
      Node* right;
      int npl;

      Node( const Comparable & e, Node* lt=nullptr, Node* rt=nullptr, int np=0 )
        : element(e), left(lt), right(rt), npl(np)
      { /*empty body*/ }
    }

    Node* root;

    Node* merge( Node* h1, Node* h2 );
    Node* merge1( Node* h1, Node* h2 );
    void swapChildren( Node* p );
    void freeMemory( Node* node );
    Node* clone( Node* node ) const;
};

template <typename Comparable>
LeftistHeap<Comparable>::LeftistHeap()
  : root(nullptr)
{
  //empty body
}

template <typename Comparable>
LeftistHeap<Comparable>::~LeftistHeap()
{
  makeEmpty();
}

template <typename Comparable>
bool LeftistHeap<Comparable>::isEmpty() const
{
  return (root == nullptr);
}

template <typename Comparable>
void LeftistHeap<Comparable>::insert( const Comparable & x )
{
  root = merge( new Node(x), root );
}

template <typename Comparable>
void LeftistHeap<Comparable>::deleteMin( Comparable & minItem )
{
  // Throw exception for deleteMin from empty heap
  if( isEmpty() )
    throw invalid_arguement("deleteMin from an empty heap");

  // Assgin root's element to minItem
  minItem = root->element;

  // merge left, right sub-tree of root
  // delete root
  Node* old_root = root;
  root = merge( root->left, root->right );
  delete old_root;
}

template <typename Comparable>
void LeftistHeap<Comparable>::makeEmpty()
{
  freeMemory(root);
  root = nullptr;
}

template <typename Comparable>
void LeftistHeap<Comparable>::merge( LeftistHeap & rhs )
{
  //avoid self merging
  if( this == &rhs )
    return;
  
  root = merge( root, rhs.root )
  rhs.root = nullptr;
}

template <typename Comparable>
Node* LeftistHeap<Comparable>::merge( Node* h1, Node* h2 )
{
  if( h1 == nullptr )
    return h2;
  if( h2 == nullptr )
    return h1;
  if( h1->element < h2->element )
    return merge1( h1, h2 );
  else
    return merge1( h2, h1 );
}

template <typename Comparable>
Node* LeftistHeap<Comparable>::merge1( Node* h1, Node* h2 )
{
  if( h1->left == nullptr )
    h1->left = h2;
  else
  {
    h1->right = merge( h1->right, h2 );
    if( h1->left->npl < h1->right->npl )
      swapChildren( h1 );
      h1->npl = h1->right->npl + 1;
  }
  return h1;
}

template <typename Comparable>
void LeftistHeap<Comparable>::swapChildren( Node* p )
{
  Node* temp = p->left;
  p->left = p->right;
  p->right = temp;
}

template <typename Comparable>
void LeftistHeap<Comparable>::freeMemory( Node* node )
{
  if( node != nullptr ){
    freeMemory( node->left );
    freeMemory( node->right );
    delete node;
  }
}

template <typename Comparable>
Node* LeftistHeap<Comparable>::clone( Node* node ) const
{
  if( node == nullptr )
    return nullptr;
  else
    return new Node( node->element, clone( node->left), clone( node->right), node->npl);
}


#endif
