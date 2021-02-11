#include <iostream>
#include <vector>
#include <algorithm>
#include <set>


class Solution {
    using ElementInterator = std::vector<int>::iterator;

    std::vector<std::vector<int>> result;
    std::set<std::vector<int>> founded;

    void check (ElementInterator e1, ElementInterator e2, ElementInterator e3, std::vector<int> & nums, bool toRight)
    {
        int sum = *e1 + *e2 + *e3;

        if( e3 == nums.end() )
            return;

        std::cout << *e1 << " " << *e2  << " "<< *e3 << " sum = " << sum << std::endl;

        if (sum==0)
        {
            std::vector<int> c{*e1,*e2,*e3};
            founded.insert(c);
            if (toRight)
            {
                e2++;
                e3++;
            }
            else
            {
                if(e1 == nums.begin() )
                    return;
                e1--;
                e2--;
            }
        }
        else if (sum > 0)
        {
            if (e1 == nums.begin())
                return;
            if (!toRight)
                e2--;
            e1--;
        }
        else
        {
            if (e3 == nums.end() )
                return;
            if (toRight)
                e2++;
            e3++;
        }
        check(e1, e2, e3, nums, toRight);
    }

public:
    std::vector<std::vector<int>> threeSum(std::vector<int> & nums)
    {
        std::sort(nums.begin(), nums.end());
        std::cout << "sorted  : ";
        for (auto i : nums)
            std::cout << i << " ";
        std::cout << std::endl;

        ElementInterator zeroElement = find (nums.begin(), nums.end(), 0);

        check( (zeroElement-1), zeroElement, (zeroElement+1), nums, true );
        check( (zeroElement-1), zeroElement, (zeroElement+1), nums, false );

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
