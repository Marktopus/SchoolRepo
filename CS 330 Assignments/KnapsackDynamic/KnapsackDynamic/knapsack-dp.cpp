#include "knapsack-dp.h"
#include <iostream>
#include <numeric>
#include <limits>
#include <algorithm>// std::max is in algorithm... but std::fmax is in numeric???
#include <set> //i want to use set to store my stuff and do algo checks

typedef std::vector< std::vector<int> > Table; //2-dimensional table


void print_table(std::vector<Item> const& items, int const& W, const Table& table)
{
  int num_items = items.size();
  //print final table - for debugging?
  //do not delete this code
  if (num_items + W < 50) { //print only if table is not too big
    std::cout << "   ";
    for (int n = 0; n <= num_items; ++n) { std::cout << n << "     "; }
    std::cout << "  items\n        ";
    for (int n = 0; n<num_items; ++n) { std::cout << items[n].weight << "," << items[n].value << "   "; }
    std::cout << "\n   ";
    for (int n = 0; n <= num_items; ++n) { std::cout << "------"; }
    std::cout << std::endl;

    for (int w = 0; w <= W; ++w) {
      std::cout << w << "| ";
      for (int n = 0; n <= num_items; ++n) {
        std::cout << table[w][n] << "     ";
      }
      std::cout << std::endl;
    }
  }
  //end do not delete this code 
}

////////////////////////////////////////////////////////////
Item::Item( int const& weight, int const& value ) 
	: weight(weight), value(value) 
{
}

////////////////////////////////////////////////////////////
Item::Item( Item const& original ) 
	: weight(original.weight), value(original.value)
{
}

////////////////////////////////////////////////////////////
std::ostream& operator<< (std::ostream& os, Item const& item) {
	os << "(" << item.weight << " , " << item.value << ") ";
	return os;
}

////////////////////////////////////////////////////////////
std::istream& operator>> (std::istream& os, Item & item) {
	os >> item.weight >> item.value;
	return os;
}

////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
//the returned value is a vector of indices
std::vector<int> knapsackDP( std::vector<Item> const& items, int const& W ) 
{
	int num_items = items.size();
  Table table;
  table.resize(W + 1, std::vector<int>(num_items + 1, 0));

  for (int weightCount = 1; weightCount <= W; ++weightCount)
  {
    for (int itemCount = 1; itemCount <= num_items; ++itemCount)
    {
    
      if (weightCount >= items[itemCount - 1].weight)
      {
        table[weightCount][itemCount] =
          std::max( table[weightCount][itemCount - 1],
                    table[weightCount - items[itemCount - 1].weight][itemCount - 1] + items[itemCount - 1].value);
      }
      else
      {
        table[weightCount][itemCount] = table[weightCount][itemCount - 1];
      }
    }
  }
  

    /*  ........... */

  print_table(items, W, table);

	//figure out which items are in the bag based on the table
  std::vector<int> bag;
  std::set<int> colsUsed;
  int curRow = W;
  int curCol = num_items;
  int lastVal = table[curRow][curCol];
  int lastCol = curCol + 1;
  while (1)
  {
    if (table[curRow][curCol] != lastVal)
    {
      if (colsUsed.find(lastCol - 1) == colsUsed.end())
      {
        bag.push_back(lastCol - 1);
        colsUsed.insert(lastCol - 1);
      }

      curRow -= items[lastCol - 1].weight;
      lastVal = table[curRow][curCol];
      continue;
    }
    --lastCol;
    --curCol;
    if (curRow < 0)
    {
      break;
    }
    if (curCol < 0)
    {
      --curRow;
      if (curRow < 0)
      {
        break;
      }
      curCol = num_items;
      lastCol = num_items + 1;
      lastVal = table[curRow][curCol];
    }
  }


	return bag;
}

////////////////////////////////////////////////////////////
int valueBag( std::vector<Item> const& items, std::vector<int> const& bag ) 
{
	std::vector<int>::const_iterator  it   = bag.begin(),
		                                it_e = bag.end();

	int accum = 0;
	//std::cout << "Bag ";
	for ( ; it != it_e; ++it) { 
		accum += items[ *it ].value; 
		//std::cout << *it << " ";
	}
	//std::cout << std::endl;
	return accum;
}

////////////////////////////////////////////////////////////
//prototype
//notice that auxiliary function returns value of the vector of items
//the actual vector is determined later from the table (similar to DP solution)
int knapsackRecMemAux( std::vector<Item> const&, int const&, int, Table& );

////////////////////////////////////////////////////////////
//function to kick start
std::vector<int> knapsackRecMem( std::vector<Item> const& items, int const& W ) 
{
	int num_items = items.size();
  Table table;
  table.resize(W + 1, std::vector<int>(num_items + 1, -1));
  for (int col = 0; col <= num_items; ++col)
  {
    table[0][col] = 0;
  }

  for (int row = 0; row <= W; ++row)
  {
    table[row][0] = 0;
  }

  knapsackRecMemAux(items, W, num_items, table);

  print_table(items, W, table);

	//figure out which items are in the bag based on the table
	std::vector<int> bag;
  //figure out which items are in the bag based on the table
  std::set<int> colsUsed;
  
  int curRow = W;
  int curCol = num_items;
  int lastVal = table[curRow][curCol];
  int lastCol = curCol + 1;
  while (1)
  {
    
    if (table[curRow][curCol] != lastVal)
    {
      if (table[curRow][curCol + 1] != -1)
      {
        if (colsUsed.find(lastCol - 1) == colsUsed.end())
        {
          bag.push_back(lastCol - 1);
          colsUsed.insert(lastCol - 1);
        }
      
        curRow -= items[lastCol - 1].weight;
        lastVal = table[curRow][curCol];
        continue;
        //lastVal = table[curRow][curCol];
      }
      else
      {
        lastVal = table[curRow][curCol];
      }
    }
    --lastCol;
    --curCol;
    if (curRow < 0)
    {
      break;
    }
    if (curCol < 0)
    {
      --curRow;
      if (curRow < 0)
      {
        break;
      }
      curCol = num_items;
      lastCol = num_items + 1;
      lastVal = table[curRow][curCol];
    }
  }
	return bag;
}

////////////////////////////////////////////////////////////
//the real recursive function
int knapsackRecMemAux( std::vector<Item> const& items, int const& W, int index, Table & table ) 
{
  int result = 0;
  if (index)
  {
    if (table[W][index] < 0)
    {
      if (W < items[index - 1].weight)
      {
        result = knapsackRecMemAux(items, W, index - 1, table);
      }
      else
      {
        result = std::max(knapsackRecMemAux(items, W, index - 1, table),
                          knapsackRecMemAux(items, W - items[index - 1].weight, index - 1, table) + items[index - 1].value);
      }
      table[W][index] = result;
    }
    return table[W][index];
    
  }

  return 0;
}
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
