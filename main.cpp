#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include "BinaryHeap.h"
#include "LeftistHeap.h"
#include "SkewHeap.h"
using namespace std;

#define HEAP_NUM 3
#define SEQ_NUM 20


void generate_random_seq( const int & n, vector<int> & seq );
void sorting_procedure( const int & n, const vector<int> & seq, vector< vector<int> > & heap_results, vector< vector<int> > & heap_counts );
string vec2string( const vector<int> & vec );
void store_heap_counts( int heap_idx, string fname, const int & n, const vector< vector< vector<int> > > & cp_counts );
void store_heap_results( int heap_idx, string fname, const int & n, const vector< vector<int> > & seqs, const vector< vector< vector<int> > > & results );


int main( int argc, char** argv )
{
  vector< vector<int> > seqs;
  vector< vector< vector<int> > > results;
  vector< vector< vector<int> > > cp_counts;

  // Set n for seq number and random generation range
  int n = atoi(argv[1]);
  cout << "n = " << n << endl;

  // Test 3 heaps with 20 random input seqences
  cout << "Testing heaps with 20 random input sequence ..." << endl;
  for( int j = 0; j < seq_num; j++ ){
    // initialize seq
    vector<int> seq;

    // generate seq randomly
    generate_random_seq(n, seq);
    for( int k = 0; k < seq.size(); k++ )
      seqs[j].push_back(seq[k]);

    // set container for each heap
    vector< vector<int> > heap_counts(HEAP_SIZE);
    vector< vector<int> > heap_results(HEAP_SIZE);

    // sort the sorting procedure
    sorting_procedure( n, seq, heap_counts, heap_results );

    // push back the containers of each heap
    results.push_back( heap_results );
    cp_counts.push_back( heap_counts );
  }

  // store the heap comparison numbers for each heaps
  cout << "Storing comparison numbers for each heaps ..." << endl;
  store_heap_counts( 0, "BinaryHeap_comparison_count.txt", n, cp_counts );
  store_heap_counts( 1, "LeftistHeap_comparison_count.txt", n, cp_counts );
  store_heap_counts( 2, "SkewHeap_comparison_count.txt", n, cp_counts );

  // store the heap results for each heaps
  cout << "Storing sorting result for each heaps ..." << endl;
  store_heap_results( 0, "BinaryHeap_sorting_result.txt", n, seqs, results );
  store_heap_results( 1, "LeftistHeap_sorting_result.txt", n, seqs, results );
  store_heap_results( 2, "SkewHeap_sorting_result.txt", n, seqs, results );
}

void generate_random_seq( const int & n, vector<int> & seq )
{
  int rand_num;
  int max = n*n;
  srand( time(NULL) );
  for( int i = 0; i < n; i++ ){
    rand_num = 1 + ( rand() % (max) )
    seq.push_back( rand_num );
  }
}

void sorting_procedure( const int & n, const vector<int> & seq, vector< vector<int> > & heap_results, vector< vector<int> > & heap_counts )
{
  int minItem;

  // declare 3 kinds of heaps
  BinaryHeap<int> E1;
  LeftistHeap<int> E2;
  SkewHeap<int> E3;

  // insert the seq serially into the 3 heap
  for( int k = 0; k < n; k ++ ){
    E1.insert( seq[k] );
    E2.insert( seq[k] );
    E3.insert( seq[k] );
  }

  // compute cp number for serial insertion
  heap_counts[0].push_back( E1.getComparisonNum() );
  heap_counts[1].push_back( E2.getComparisonNum() );
  heap_counts[2].push_back( E3.getComparisonNum() );

  // pop the seq out by serial deleteMin operations
  while( !E1.isEmpty() ){
    E1.deleteMin( minItem );
    heap_results[0].push_back( minItem );
  }
  while( !E2.isEmpty() ){
    E2.deleteMin( minItem );
    heap_results[1].push_back( minItem );
  }
  while( !E3.isEmpty() ){
    E3.deleteMin( minItem );
    heap_results[2].push_back( minItem );
  }

  // compute cp number for serial deleteMin
  heap_counts[0].push_back( E1.getComparisonNum() - heap_counts[0][0] );
  heap_counts[1].push_back( E2.getComparisonNum() - heap_counts[1][0] );
  heap_counts[2].push_back( E3.getComparisonNum() - heap_counts[2][0] );

  // compute total cp number
  heap_counts[0].push_back( heap_counts[0][1] + heap_counts[0][0] );
  heap_counts[1].push_back( heap_counts[1][1] + heap_counts[1][0] );
  heap_counts[2].push_back( heap_counts[2][1] + heap_counts[2][0] );
}

string vec2string( const vector<int> & vec )
{
  string line;
  for( int i = 0; i < vec.size(); i++ )
    line = line + to_string(vec[i]) + "\t";
  return line;
}

void store_heap_counts( int heap_idx, string fname, const int & n, const vector< vector< vector<int> > > & cp_counts )
{
  ofstream f;
  f.open( fname.c_str(), ios::out );
  f << "n = " << n << endl;
  for( int i = 0; i < SEQ_NUM; i++ ){
    f << "insertion: " << to_string( cp_counts[i][heap_idx][0] ) << "\n";
    f << "deleteMin: " << to_string( cp_counts[i][heap_idx][1] ) << "\n";
    f << "total: " << to_string( cp_counts[i][heap_idx][2] ) << "\n";
  }
  f.close();
}

void store_heap_results( int heap_idx, string fname, const int & n, const vector< vector<int> > & seqs, const vector< vector< vector<int> > > & results )
{
  ofstream f;
  f.open( fname.c_str(), ios::out );
  f << "n = " << n << endl;
  for( int i = 0; i < SEQ_NUM; i++ )
    f << vec2string( results[i][heap_idx] ) << "\n";
  f.close();
}
