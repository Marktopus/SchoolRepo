#ifndef PERM_JOHNSON_TROTTER_H
#define PERM_JOHNSON_TROTTER_H
#include <vector>
#include <algorithm>
#include <utility>
class PermJohnsonTrotter 
{
  public:
    PermJohnsonTrotter(int size);
    bool Next();
    std::vector<int> const& Get() const;
  private:
    std::vector<int> permutations_;

    //false is left, true is right
    std::vector<bool> directions_;
    
    void swap_entries(int first, int second);

    //returns by index
    int find_largest_mobile_integer();

};

#endif
