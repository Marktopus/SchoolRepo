#include "perm-jt.h"

PermJohnsonTrotter::PermJohnsonTrotter(int size) :  permutations_(std::vector<int>()),
                                                    directions_(std::vector<bool>())
{
  permutations_.resize(size);
  directions_.resize(size);//inits to false
  while (size > 0)
  {
    permutations_[size - 1] = size;
    --size;
  }
}

bool PermJohnsonTrotter::Next()
{
  //returns index
  int largestMobileIndex = find_largest_mobile_integer();
  if (largestMobileIndex == -1)
  {
    return false;
  }
  int largestMobileInt = permutations_[largestMobileIndex];
  if (directions_[largestMobileIndex]) //right
  {
    swap_entries(largestMobileIndex, largestMobileIndex + 1);
  }
  else // left
  {
    swap_entries(largestMobileIndex, largestMobileIndex - 1);
  }

  for (int i = 0; i < static_cast<int>(permutations_.size()); ++i)
  {
    if (permutations_[i] > largestMobileInt)
    {
      directions_[i] = !directions_[i];
    }
  }
  return true;
}

std::vector<int> const& PermJohnsonTrotter::Get() const
{
  return permutations_;
}

void PermJohnsonTrotter::swap_entries(int first, int second)
{
  int tempInt = permutations_[first];
  permutations_[first] = permutations_[second];
  permutations_[second] = tempInt;

  bool tempBool = directions_[first];
  directions_[first] = directions_[second];
  directions_[second] = tempBool;

}

int PermJohnsonTrotter::find_largest_mobile_integer()
{
  int largestIndex = -1;
  int largestNumber = 0;
  for (int i = 0; i < static_cast<int>(permutations_.size()); ++i)
  {
    if (directions_[i]) // right
    {
      if ((i < (static_cast<int>(permutations_.size()) - 1)) && (permutations_[i] > permutations_[i + 1]))
      {
        //it's mobile
        if (permutations_[i] > largestNumber)
        {
          largestNumber = permutations_[i];
          largestIndex = i;
        }
      }
    }
    else //left
    {
      if (i && (permutations_[i - 1] < permutations_[i]))
      {
        //it's mobile
        if (permutations_[i] > largestNumber)
        {
          largestNumber = permutations_[i];
          largestIndex = i;
        }
      }
    }
  }
  return largestIndex;
}

