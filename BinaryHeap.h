#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include "stdexcept"
#include <vector>
#include <iostream>
using namespace std;

template <typename Comparable>
class BinaryHeap
{
  public:
    explicit BinaryHeap( int capacity = 100 );
    explicit BinaryHeap( const vector<Comparable> & items );
    bool isEmpty() const;
    const Comparable & findMin() const;
    void insert( const Comparable & x );
    void deleteMin( Comparable & minItem );
    void makeEmpty();
    void printHeap() const;

  private:
    int currentSize;
    vector<Comparable> array;
    
    void buildHeap();
    void percolateDown(int i);
    void percolateUp(int i);
    void swap(int i, int j);
};

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( int capacity )
  : array(capacity + 1), currentSize(0) 
{
  //empty body
}

template <typename Comparable>
BinaryHeap<Comparable>::BinaryHeap( const vector<Comparable> & items )
  : array( items.size() + 100 ), currentSize(items.size())
{
  for( int i = 0; i < items.size(); ++i )
    array[i+1] = items[i];
  buildHeap();
}

template <typename Comparable>
bool BinaryHeap<Comparable>::isEmpty() const
{
  return (currentSize == 0);
}

template <typename Comparable>
const Comparable & BinaryHeap<Comparable>::findMin() const
{
  return array[1];
}

template <typename Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x )
{
  // enlarge the size of array by an amount of 100 
  // if the insertion would exceed max size of heap
  if( currentSize + 1 == array.size() )
    array.resize( array.size() + 100 );

  //increment current size, push x into back of array
  currentSize++;
  array[currentSize] = x;

  //percolate x up to its final position in heap
  percolateUp(currentSize);
}

template <typename Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
{
  //test if heap is empty
  if( isEmpty() )
    throw invalid_argument("deleteMin from an empty heap");

  // set minItem to the minimun element in heap
  minItem = array[1];

  // swap the last element to position 1 and decrement heap size by 1
  // then percolate it down
  swap(1, currentSize);
  currentSize--;
  percolateDown(1);
}

template <typename Comparable>
void BinaryHeap<Comparable>::makeEmpty()
{
  //clear the array, resize it to capacity of 100
  //set current size to 0
  array.clear();
  array.resize(101);
  currentSize = 0;
}

template <typename Comparable>
void BinaryHeap<Comparable>::printHeap() const
{
  for(int i = 1; i <= currentSize; i++)
    cout << array[i] << " ";
  cout << endl;
}

template <typename Comparable>
void BinaryHeap<Comparable>::buildHeap()
{
  for( int i = currentSize/2; i >= 1; i-- )
    percolateDown(i);
}

template <typename Comparable>
void BinaryHeap<Comparable>::percolateDown(int i)
{
  // keep swapping until element of index i
  // percolate down to its final position
  int pos = i;
  while( pos*2 <= currentSize ){
    int left = 2*pos;
    int right = 2*pos + 1;

    // case where array[pos] has only left child
    if( left == currentSize && array[left] < array[pos] ){
      swap(pos, left);
      pos = left;
      break;
    }
    else if( left == currentSize && array[left] >= array[pos] )
      break;

    // case where array[pos] has both its children
    if( array[left] <= array[pos] || array[right] <= array[pos] ){
      if( array[left] <= array[right] ){
        swap(pos, left);
        pos = left;
      }
      else if( array[right] < array[left] ){
        swap(pos, right);
        pos = right;
      }
    }
    else
      break;
  }
}

template <typename Comparable>
void BinaryHeap<Comparable>::percolateUp(int i)
{
  // keep swapping until element of index i
  // percolate up to its final position
  int pos = i;
  while( pos >= 1 ){
    int parent_pos = pos / 2;
    if( array[pos] < array[parent_pos] )
      swap(pos, parent_pos);
    pos = parent_pos;
  }
}

template <typename Comparable>
void BinaryHeap<Comparable>::swap(int i, int j)
{
  //swap the elements of index i and j
  Comparable temp;
  temp = array[i];
  array[i] = array[j];
  array[j] = temp;
}

#endif
