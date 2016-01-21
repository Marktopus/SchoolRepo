#ifndef KNAPSACK_BB_H
#define KNAPSACK_BB_H
#include <vector>
#include <climits>
#include <fstream> //ostream, istream
#include <iostream>

class Item {
	public:
		Item( int const& weight = 0, int const& value = 0 );
		Item( Item const& original );
        bool operator<( Item const& arg2 ) const;
		int weight;
		int value;
	private:
};

std::ostream& operator<< (std::ostream& os, Item const& item);
std::istream& operator>> (std::istream& os, Item & item);

template <typename T> void print(const T& v) {
    typename T::const_iterator iter = v.begin();
    std::cout <<  "{ ";
    if ( iter != v.end() ) {
        std::cout <<  *iter;
        ++iter;
        for ( ; iter != v.end(); ++iter) std::cout << "," << *iter;
    }
    std::cout <<  " } ";
}

//plain vanilla backtracking
std::vector<int> knapsack_backtracking( std::vector<Item> const& items, int const& W );

//backtracking with upper bound optimization
std::vector<int> knapsack_backtracking_branchbound( std::vector<Item> const& items, int const& W );

#endif
