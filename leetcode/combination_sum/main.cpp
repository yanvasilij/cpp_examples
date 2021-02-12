#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		vector<int>cur_path;
		len = candidates.size();
		dfs ( candidates, target, cur_path, 0 );
		return ans;
	}

private:
	vector<vector<int>> ans;
	int len;
	
	void dfs ( vector<int> &candidates, int target, vector<int> &cur_path, int start )
	{
		if ( target < 0 ) return;
		if ( target == 0 )
		{
			ans.push_back(cur_path);
			return;
		}
		
		for ( ; start < len; ++start )
		{
			cur_path.push_back( candidates[start] );
			dfs ( candidates, target - candidates[start], cur_path, start );
			cur_path.pop_back();
		}
	}
};



int main( )
{
    Solution solution;

    int target = 7;
    vector<int> in{2,3,6,7};

    auto r = solution.combinationSum(in, target);

    for (auto i : r)
	{
		std::cout << "# ";
		for (auto j : i)
		{
			std::cout << j << " ";
		}
		std::cout << std::endl;
	}

    return 0;
}
