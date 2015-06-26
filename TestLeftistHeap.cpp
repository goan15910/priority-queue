#include <iostream>
#include <vector>
#include <string>
#include "LeftistHeap.h"
using namespace std;

int main()
{
  int minItem;
  LeftistHeap<int> h;
  int item_list[] = { 9, 3, 5, 6, 7, 1, 2, 4, 7, 8};
  vector<int> temp;

  //Initialize items
  vector<int> items ( item_list, item_list + sizeof(item_list)/sizeof(int) );
  cout << "Initialize vector with:" << endl;
  for(int i = 0; i < items.size(); i++ )
    cout << items[i] << " ";
  cout << endl;

  //Test for serial insertion
  cout << "\nTest for serial insertion" << endl;
  for( int i = 0; i < items.size(); i++ )
    h.insert(items[i]);
  cout << "Heap after serial insertion" << endl;
  h.printHeap();
  cout << endl;

  temp.clear();
  while( !h.isEmpty() ){
    h.deleteMin(minItem);
    temp.push_back(minItem);
    h.printHeap();
  }

  cout << "The output sequence of serial deleteMin" << endl;
  for( int i = 0; i < temp.size(); i++ )
    cout << temp[i] << " ";
  cout << endl;

}
