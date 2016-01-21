#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>

bool nextPermLexicographical (std::vector<int> & p) 
{
  // p is our permutation
  int firstIndex = -1;
  bool retVal = false;
  int iter;
  for (iter = p.size() - 1; iter > 0; --iter)
  {
    if (p[iter - 1] < p[iter])
    {
      firstIndex = iter;
      break;
    }
  }

  if (firstIndex == -1)
  {
    return retVal;
  }

  for (iter = p.size() - 1; iter > 0; --iter)
  {
    if ((iter >= firstIndex) && (p[iter] > p[firstIndex - 1]))
    {
      std::swap(p[iter], p[firstIndex - 1]);
      retVal = true;
      break;
    }
  }

  //use largestDiff now for iteration
  int endIter = p.size() - 1;
  while (endIter > firstIndex)
  {
    std::swap(p[endIter], p[firstIndex]);
    --endIter;
    ++firstIndex;
  }
  return retVal;
}
