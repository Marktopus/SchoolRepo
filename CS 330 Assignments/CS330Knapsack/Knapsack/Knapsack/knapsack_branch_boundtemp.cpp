//#include "knapsack_branch_bound.h"
//
//Item::Item(int const& weight, int const& value) : weight(weight),
//                                                  value(value)
//{
//
//}
//
//Item::Item(Item const& original)  : weight(original.weight),
//                                    value(original.value)
//{
//
//}
//
//bool Item::operator<(Item const& arg2) const
//{
//  return (static_cast<float>(value) / static_cast<float>(weight)) < 
//    (static_cast<float>(arg2.value) / static_cast<float>(arg2.weight));
//}
//
//int find_value(std::vector<Item> const& items, std::vector<int> const& indices)
//{
//  int retVal = 0;
//  if (!indices.empty())
//  {
//    if (indices.front() == -1)
//    {
//      return -INT_MAX;
//    }
//  }
//  for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); ++it)
//  {
//    retVal += items[*it].value;
//  }
//  return retVal;
//}
//
//int find_weight(std::vector<Item> const& items, std::vector<int> const& indices)
//{
//  int retVal = 0;
//  if (!indices.empty())
//  {
//    if (indices.front() == -1)
//    {
//      return -INT_MAX;
//    }
//  }
//  for (std::vector<int>::const_iterator it = indices.begin(); it != indices.end(); ++it)
//  {
//    retVal += items[*it].weight;
//  }
//  return retVal;
//}
//
////note: this works, but not the way volper wants it to
////std::set<int> knapsack_backtracking(std::vector<Item> const& items, std::set<int> const& currentIndices, int const& W)//W is max weight. 
////{
////  std::set<int> iterIndices = currentIndices;//our iterator indices, which we change iteratively
////  std::set<int> newIndices = currentIndices;//set of indices we get every loop
////  std::set<int> bestIndices = currentIndices;//the best total indices in our iteration
////
////  int newValue = find_value(items, iterIndices);
////  int newWeight;
////  int bestValue = newValue;//must be better than our current value to be marked best
////  for (int i = 0; i < items.size(); ++i)
////  {
////    if (iterIndices.find(i) == iterIndices.end())//if it's a dupilcate, ignore it
////    {
////      iterIndices.insert(i);//insert our new index
////      newWeight = find_weight(items, iterIndices);//find weight with that index
////      if (newWeight <= W)//if that weight is too heavy, then ditch it
////      {
////        newIndices = knapsack_backtracking(items, iterIndices, W);//find our new set of indices
////        newValue = find_value(items, newIndices);//new value calc
////        if (newValue > bestValue) // if the new value is better than our best, set our best to our new
////        {
////          bestIndices = newIndices;
////          bestValue = newValue;
////        }
////      }
////      iterIndices.erase(i);//get rid of the index we just added in prep for next iteration
////    }
////  }
////  return bestIndices;
////}
//
//std::vector<int> knapsack_backtracking(std::vector<Item> const& items, std::vector<int> indices, 
//                                        int const& W, std::vector<int>& bestSoFar)//W is max weight. 
//{
//  for (size_t i = 0; i < items.size(); ++i)
//  {
//    if (indices.empty() || (static_cast<int>(i) > indices.back()))
//    {
//      indices.push_back(i);
//      int curWeight = find_weight(items, indices);
//      if (curWeight <= W)
//      {
//        std::vector<int> newBest = knapsack_backtracking(items, indices, W, bestSoFar);
//        int newValue = find_value(items, newBest);
//        int newWeight = find_weight(items, newBest);
//        if (newValue > find_value(items, bestSoFar))
//        {
//          if (items.size() < 20)
//          {
//            printf("Base case: bag { %d", newBest.front());
//            for (size_t i = 1; i < newBest.size(); ++i)
//            {
//              printf(",%d", newBest[i]);
//            }
//            printf(" } weight=%d, value=%d - is new best (old best=%d)\n", newWeight, newValue, find_value(items, bestSoFar));
//          }
//          bestSoFar = newBest;
//        }
//        else
//        {
//          if (items.size() < 20)
//          {
//            printf("Base case: bag{ %d", newBest.front());
//            for (size_t i = 1; i < newBest.size(); ++i)
//            {
//              printf(",%d", newBest[i]);
//            }
//            printf(" } weight=%d, value=%d - is not better then previous best (%d)\n", newWeight, newValue, find_value(items, bestSoFar));
//          }
//        }
//      }
//      indices.pop_back();
//    }
//  }
//  return indices;
//}
//
//
////plain vanilla backtracking
//std::vector<int> knapsack_backtracking(std::vector<Item> const& items, int const& W)//W is max weight. 
//{
//  std::vector<int> indices;
//  std::vector<int> best;
//  best.push_back(-1);
//  indices = knapsack_backtracking(items, indices, W, best);
//  if (items.size() < 20)
//  {
//    if (0 > find_value(items, best))
//    {
//      printf("Base case: bag {  } weight=0, value=0 - is new best (old best=%d)\n", find_value(items, best));
//      best = indices;
//    }
//    else
//    {
//      printf("Base case: bag {  } weight=0, value=0 - is not better then previous best (%d)\n", find_value(items, best));
//    }
//  }
//
//  //fill stdvector with my set
//  return best;
//}
//
////backtracking with upper bound optimization
//std::vector<int> knapsack_backtracking_branchbound(std::vector<Item> const& items, int const& W)
//{
//  return std::vector<int>();
//}
//
//std::ostream& operator<< (std::ostream& os, Item const& item)
//{
//  os << "(" << item.weight << "," << item.value << ")";
//  return os;
//}
//
//std::istream& operator>> (std::istream& os, Item & item)
//{
//  os >> item.weight >> item.value;
//  return os;
//}