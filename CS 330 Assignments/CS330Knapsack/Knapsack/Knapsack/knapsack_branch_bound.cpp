#include "knapsack_branch_bound.h"
#include <limits>

////////////////////////////////////////////////////////////////////////////////
Item::Item(int const& weight, int const& value)
  : weight(weight), value(value)
{
}

////////////////////////////////////////////////////////////////////////////////
Item::Item(Item const& original)
  : weight(original.weight), value(original.value)
{
}

////////////////////////////////////////////////////////////////////////////////
bool Item::operator<(Item const& arg2) const { //compare values per unit of weight
  //return static_cast<double>(value)/weight < static_cast<double>(arg2.value)/arg2.weight;
  return value*arg2.weight < arg2.value*weight; //same logic, but faster
}

////////////////////////////////////////////////////////////////////////////////
std::ostream& operator<< (std::ostream& os, Item const& item) {
  os << "(" << item.weight << "," << item.value << ")";
  return os;
}

////////////////////////////////////////////////////////////////////////////////
std::istream& operator>> (std::istream& os, Item & item) {
  os >> item.weight >> item.value;
  return os;
}

int find_value(std::vector<Item> const& items, std::vector<int> const& indices)
{
  int retVal = 0;
  for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); ++it)
  {
    retVal += items[*it].value;
  }
  return retVal;
}

int find_weight(std::vector<Item> const& items, std::vector<int> const& indices)
{
  int retVal = 0;
  for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); ++it)
  {
    retVal += items[*it].weight;
  }
  return retVal;
}


////////////////////////////////////////////////////////////////////////////////
//prototype
void knapsack_backtracking_rec(
  std::vector<Item> const& items, int const& W,             //problem data
  std::vector<int> & best_bag_sofar, int & best_value_sofar,//best bag so far
  std::vector<int> & bag, int & value, int & weight,//current bag
  unsigned depth                                            //current depth of recursion
  );

////////////////////////////////////////////////////////////////////////////////
//the returned value is a vector of indices
std::vector<int> knapsack_backtracking(
  std::vector<Item> const& items,
  int const& W)
{
  //data to keep track of the best so far
  std::vector<int> best_bag_sofar;
  int              best_value_sofar = std::numeric_limits<int>::min();

  //data to keep track of the current bag
  std::vector<int> bag; bag.reserve(items.size());
  int              value = 0;
  int              weight = 0;

  //print ( items );
  //std::cout << std::endl << "=========================" << std::endl;

  //kick-start recursion
  knapsack_backtracking_rec(
    items, W,                         //problem data
    best_bag_sofar, best_value_sofar, //best bag so far
    bag, value, weight,               //current bag
    0                                 //current depth of recursion
    );

  return best_bag_sofar;

}

////////////////////////////////////////////////////////////////////////////////
void knapsack_backtracking_rec(
  std::vector<Item> const& items, int const& W,             //problem data
  std::vector<int> & best_bag_sofar, int & best_value_sofar,//best bag so far
  std::vector<int> & bag, int & value, int & weight,//current bag
  unsigned depth                                            //current depth of recursion
  )
{
  unsigned max_size_to_print = 12;
  //recursion through all subsets, based on "take/not take" current item (take is first)
  if (weight > W)
  {
    return;
  }
  
  //base case
  if ((items.size() == depth) || (weight > W)) 
  {
    if (items.size() < max_size_to_print) 
    {
      std::cout << "Base case: bag ";
      print(bag);
      std::cout << "weight=" << weight << ", value=" << value;
    }
    if (value > best_value_sofar) 
    {
      if (items.size() < max_size_to_print) 
      {
        std::cout << " - is new best (old best=" << best_value_sofar << ")\n";
      }
      best_value_sofar = value;
      best_bag_sofar = bag;
    }
    else 
    {
      if (items.size() < max_size_to_print) 
      {
        std::cout << " - is not better then previous best (" << best_value_sofar << ")\n";
      }
    }
    return;
  }

  //general case
  bag.push_back(depth);
  value += items[depth].value;
  weight += items[depth].weight;
  knapsack_backtracking_rec(items, W,
                            best_bag_sofar, best_value_sofar,
                            bag, value, weight,
                            depth + 1);

  bag.pop_back();
  value -= items[depth].value;
  weight -= items[depth].weight;
  knapsack_backtracking_rec(items, W,
                            best_bag_sofar, best_value_sofar,
                            bag, value, weight,
                            depth + 1);
}

////////////////////////////////////////////////////////////////////////////////
//prototype
void knapsack_backtracking_branchbound_rec(
  std::vector<Item> const& items, int const& W,             //problem data
  std::vector<int> & best_bag_sofar, int & best_value_sofar,//best bag so far
  std::vector<int> & bag, int & value, int & weight,//current bag
  unsigned depth                                            //current depth of recursion
  );

////////////////////////////////////////////////////////////////////////////////
std::vector<int> knapsack_backtracking_branchbound(
  std::vector<Item> const& items,
  int const& W)
{
  //data to keep track of the best so far
  std::vector<int> best_bag_sofar;
  int              best_value_sofar = std::numeric_limits<int>::min();

  //data to keep track of the current bag
  std::vector<int> bag; bag.reserve(items.size());
  int              value = 0;
  int              weight = 0;

  //print ( items );
  //std::cout << std::endl << "=========================" << std::endl;

  //kick-start recursion
  knapsack_backtracking_branchbound_rec(
    items, W,                         //problem data
    best_bag_sofar, best_value_sofar, //best bag so far
    bag, value, weight,               //current bag
    0                                 //current depth of recursion
    );

  return best_bag_sofar;

}

////////////////////////////////////////////////////////////////////////////////
void knapsack_backtracking_branchbound_rec(
  std::vector<Item> const& items, int const& W,             //problem data
  std::vector<int> & best_bag_sofar, int & best_value_sofar,//best bag so far
  std::vector<int> & bag, int & value, int & weight,//current bag
  unsigned depth                                            //current depth of recursion
  )
{
  unsigned max_size_to_print = 12;
  //recursion through all subsets, based on "take/not take" current item (take is first)

  if (weight > W)
  {
    return;
  }

  //base case
  if ( (depth == items.size()) || (weight > W)) 
  {
    if (items.size() < max_size_to_print) 
    {
      std::cout << "Base case: bag ";
      print(bag);
      std::cout << "weight=" << weight << ", value=" << value;
    }
    if (value > best_value_sofar) 
    {
      if (items.size() < max_size_to_print) 
      {
        std::cout << " - is new best (old best=" << best_value_sofar << ")\n";
      }
      best_value_sofar = value;
      best_bag_sofar = bag;
    }
    else 
    {
      if (items.size() < max_size_to_print) 
      {
        std::cout << " - is not better then previous best (" << best_value_sofar << ")\n";
      }
    }
    return;
  }

  //upper bound check
  //assume items are in decreasing order of value/weight ratio, so that 
  //continuous knapsack prefers items starting in the beginning of the list 
  int remaining_capacity = W - weight;
  double upper_bound = 0;
  unsigned depthIter = depth + 1;
  //calculate upper bound
  while (depthIter < items.size())
  {
    if (items[depthIter].weight <= remaining_capacity)
    {
      remaining_capacity -= items[depthIter].weight;
      upper_bound += items[depthIter].value;
    }
    else
    {
      float formulaOutput = static_cast<float>(items[depthIter].value) * (static_cast<float>(remaining_capacity) / static_cast<float>(items[depthIter].weight));
      upper_bound += formulaOutput;
      remaining_capacity -= formulaOutput;
    }
    ++depthIter;
  }

  if ((value + upper_bound) < best_value_sofar) 
  {
    if (items.size() < max_size_to_print) 
    {
      std::cout << "Cancel branch" << std::endl;
    }
    return;
  }

  //general case

  //general case
  bag.push_back(depth);
  value += items[depth].value;
  weight += items[depth].weight;
  knapsack_backtracking_branchbound_rec(items, W,
    best_bag_sofar, best_value_sofar,
    bag, value, weight,
    depth + 1);

  bag.pop_back();
  value -= items[depth].value;
  weight -= items[depth].weight;
  knapsack_backtracking_branchbound_rec(items, W,
    best_bag_sofar, best_value_sofar,
    bag, value, weight,
    depth + 1);

}
////////////////////////////////////////////////////////////////////////////////