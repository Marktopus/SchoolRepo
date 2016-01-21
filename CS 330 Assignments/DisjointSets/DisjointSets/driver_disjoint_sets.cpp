/*!
  \file   disjoint_sets_test.cpp
  \author Dmitri Volper
  \par    email: dvolper\@digipen.edu
  \date   Tue 29 Jun 2010 09:03:15 PM PDT
  \short  test cases for disjoint subsets.
*/
#include <iostream>
#include "disjoint_sets.h"

void test0() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test1() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	ds.Join(1,0);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test2() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	ds.Join(0,1);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test3() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	ds.Join(0,1);
  std::cout << ds << std::endl;

  for (int i = 0; i<10; ++i)
    std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
	ds.Join(0,2);
  std::cout << ds << std::endl;

  for (int i = 0; i<10; ++i)
    std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
	ds.Join(0,3);
  std::cout << ds << std::endl;

  for (int i = 0; i<10; ++i)
    std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
	ds.Join(0,4);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test4() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	ds.Join(1,0);
	ds.Join(2,0);
	ds.Join(3,0);
	ds.Join(4,0);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test5() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	ds.Join(1,0);
	ds.Join(0,2);
	ds.Join(3,0);
	ds.Join(0,4);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test6() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	for (int i=1; i<10; ++i ) ds.Join(0,i);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test7() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	for (int i=1; i<10; ++i ) ds.Join(i,0);
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test8() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	for (int i=1; i<10; i+=2 ) { 
		ds.Join(i,0);
    std::cout << ds << std::endl;
		ds.Join(0,i); 
    std::cout << ds << std::endl;
	}
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test9() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	for (int i=1; i<10; i+=2 ) {
		ds.Join(i,0);
		ds.Join(0,i);
	}
	std::cout << ds << std::endl;

	for (int i=0; i<10; ++i ) 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
}

void test10() {
	DisjointSets ds(10);
	for (int i=0; i<10; ++i ) ds.Make( );

	//test self-join
	ds.Join(0,1);
	ds.Join(0,1);
	ds.Join(1,0);
	std::cout << ds << std::endl;
	for (int i=0; i<10; ++i ) { 
		std::cout << i << " -> " << ds.GetRepresentative(i) << std::endl;
	}
}

void (*pTests[])(void) = { test0,test1,test2,test3,test4,test5,test6,test7,test8,test9,test10 };

int main( int argc, char ** argv) try {
	if (argc!=2) return 1;
	else {
		int test = 0;
		std::sscanf(argv[1],"%i",&test);
		pTests[ 10 ]();
	}
	return 0;
} catch ( char const* e ) {
	std::cout << e << std::endl;
}

