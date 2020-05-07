#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
public:
  vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> m;
    int i, j;

    for (i = 0; i < nums.size(); i++) {
      int num_1 = nums[i];
      int num_2 = target - num_1;
      if (m.find(num_2) != m.end()) {
        j = m[num_2];
        break;
      }
      m[num_1] = i;
    }

    vector<int> result;
    result.push_back(i);
    result.push_back(j);
    return result;
  }
};

int main() {
  // int a[] = {2, 7, 11, 15};
  // int target = 9;
  int a[] = {3, 2, 4};
  int target = 6;
  vector<int> nums(a, a+sizeof(a)/sizeof(a[0]));
  auto result = Solution().twoSum(nums, target);
  cout << result[0] << " " << result[1] << endl;
  return 0;
}
