#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


class Solution {
    using ElementInterator = std::vector<int>::iterator;

    std::vector<std::vector<int>> result;
    std::set<std::vector<int>> founded;

    void check (ElementInterator e1, ElementInterator e2, ElementInterator e3, std::vector<int> & nums, int lastSum)
    {
        int sum = *e1 + *e2 + *e3;
        std::cout << "sum: " << sum << "-> " << *e1 << " " << *e2 << " " << *e3 << std::endl;
        if (sum > 0)
        {
            if ( ((e2-1) != e1) && (lastSum > 0))
            {
                e2--;
            }
            else
            {
                if (e1 == nums.begin())
                    return;
                e1--;
            }
        }
        else if(sum<0)
        {
            if ( ((e1+1) != e3) && (lastSum < 0) )
            {
                e2++;
            }
            else
            {
                if (e3 == (nums.end()-1))
                    return;
                e3++;
            }
        }
        else
        {
            founded.insert(std::vector<int>{*e1, *e2, *e3});
            if (e3 != (nums.end() - 1) )
                e3++;
            else if (e1 != nums.begin())
                e1--;
            else
                return;
        }
        check(e1, e2, e3, nums, sum);
    }

public:
    std::vector<std::vector<int>> threeSum(std::vector<int> & nums)
    {
        std::sort(nums.begin(), nums.end());
        std::cout << "sorted  : ";
        for (auto i : nums)
            std::cout << i << " ";
        std::cout << std::endl;

        if (nums.size() < 3)
            return std::vector<std::vector<int>> {};

        ElementInterator zeroElement = nums.begin() + nums.size()/2;

        check( (zeroElement-1), zeroElement, (zeroElement+1), nums, 0 );

        for (auto i : founded)
            result.push_back(i);

        return result;
    }
};

int main( )
{
    Solution solution;

    std::vector<int> in{3,0,-2,-1,1,2};

    auto result = solution.threeSum(in);

    for (auto & i : result)
    {
        std::cout << "#";
        for (auto & j : i)
            std::cout << j << " ";
        std::cout << std::endl;
    }

    std::cout << "done" << std::endl;
    return 0;
}
