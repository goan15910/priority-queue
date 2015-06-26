#ifndef SKEW_HEAP_H
#define SKEW_HEAP_H

#include <iostream>
#include <stdexcept>
using namespace std;

template <typename Comparable>
class SkewHeap
{
  public:
    SkewHeap();
    ~SkewHeap();
    bool isEmpty() const;
    void insert( const Comparable & x );
    void deleteMin( Comparable & minItem );
    void makeEmpty();
    void merge( SkewHeap & rhs );
    void printHeap() const;
    int getComparisonNum() const;

  private:
    struct Node
    {
      Comparable element;
      Node* left;
      Node* right;

      Node( const Comparable & e, Node* lt=nullptr, Node* rt=nullptr )
        : element(e), left(lt), right(rt)
      { /*empty body*/ }
    };

    Node* root;
    int comparison_num;

    void swapChildren( Node* p );
    void freeMemory( Node* node );
    void printHeap( Node* node ) const;

    Node* merge( Node* h1, Node* h2 )
    {
      if( h1 == nullptr )
        return h2;
      if( h2 == nullptr )
        return h1;
      if( h1->element < h2->element ){
        comparison_num++;
        return merge1( h1, h2 );
      }
      else{
        comparison_num++;
        return merge1( h2, h1 );
      }
    }

    Node* merge1( Node* h1, Node* h2 )
    {
      if( h1->left == nullptr )
        h1->left = h2;
      else{
        h1->right = merge( h1->right, h2 );
        swapChildren( h1 );
      }
      return h1;
    }

};

template <typename Comparable>
SkewHeap<Comparable>::SkewHeap()
  : root(nullptr), comparison_num(0)
{
  //empty body
}

template <typename Comparable>
SkewHeap<Comparable>::~SkewHeap()
{
  makeEmpty();
}

template <typename Comparable>
bool SkewHeap<Comparable>::isEmpty() const
{
  return (root == nullptr);
}

template <typename Comparable>
void SkewHeap<Comparable>::insert( const Comparable & x )
{
  root = merge( new Node(x), root );
}

template <typename Comparable>
void SkewHeap<Comparable>::deleteMin( Comparable & minItem )
{
  // Throw exception for deleteMin from empty heap
  if( isEmpty() )
    throw invalid_argument("deleteMin from an empty heap");

  // Assgin root's element to minItem
  minItem = root->element;

  // merge left, right sub-tree of root
  // delete root
  Node* old_root = root;
  root = merge( root->left, root->right );
  delete old_root;
}

template <typename Comparable>
void SkewHeap<Comparable>::makeEmpty()
{
  freeMemory(root);
  root = nullptr;
}

template <typename Comparable>
void SkewHeap<Comparable>::merge( SkewHeap & rhs )
{
  //avoid self merging
  if( this == &rhs )
    return;
  
  root = merge( root, rhs.root );
  rhs.root = nullptr;
}

template <typename Comparable>
void SkewHeap<Comparable>::printHeap() const
{
  if( root != nullptr )
    printHeap(root);
  cout << endl;
}

template <typename Comparable>
int SkewHeap<Comparable>::getComparisonNum() const
{
  return comparison_num;
}

template <typename Comparable>
void SkewHeap<Comparable>::swapChildren( Node* p )
{
  Node* temp = p->left;
  p->left = p->right;
  p->right = temp;
}

template <typename Comparable>
void SkewHeap<Comparable>::freeMemory( Node* node )
{
  if( node != nullptr ){
    freeMemory( node->left );
    freeMemory( node->right );
    delete node;
  }
}

template <typename Comparable>
void SkewHeap<Comparable>::printHeap( Node* node ) const
{
  if( node->left != nullptr )
    printHeap(node->left);
  cout << node->element << " ";
  if( node->right != nullptr )
    printHeap(node->right);
}


#endif
