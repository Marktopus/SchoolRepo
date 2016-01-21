#include "lis.h"
#include <algorithm>
std::vector<unsigned> longest_increasing_subsequence( std::vector<int> const& sequence ) 
{
  //allocated/reserve table, init all to 0 - including init case

  std::vector<unsigned> curSubsequence;
  std::vector<unsigned> previousIndices;

  curSubsequence.resize(static_cast<int>(sequence.size() + 1), 0);
  previousIndices.resize(sequence.size(), 0);

  //main logic
  int longest = 0;

  //variables for binary search
  int low;
  int high;
  int mid;

  int newLongest;
  for (int iter = 0; iter < static_cast<int>(sequence.size()); ++iter)
  {
    low = 1;
    high = longest;

    while (low <= high)
    {
      mid = (low + high) / 2;
      if (sequence[curSubsequence[mid]] < sequence[iter])
      {
        low = mid + 1;
      }
      else
      {
        high = mid - 1;
      }
    }

    newLongest = low;

    previousIndices[iter] = curSubsequence[newLongest - 1];
    curSubsequence[newLongest] = iter;

    if (newLongest > longest)
    {
      longest = newLongest;
    }
  }

  //reconstruct subsequence
  std::vector<unsigned> answer( longest,0 ); //vector of indices corresponding to the LIS
  int current = curSubsequence[longest];

  for (int iter = longest - 1; iter >= 0; --iter)
  {
    answer[iter] = current;
    current = previousIndices[current];
  }

  return answer;
}
