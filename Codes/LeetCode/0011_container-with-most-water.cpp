#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
  int maxArea(vector<int>& height) {
    int max_area = 0;
    int i = 0, j = height.size()-1;
    while (i < j) {
      int area;
      if (height[i] < height[j]) {
        area = height[i] * (j - i);
        i++;
      }
      else {
        area = height[j] * (j - i);
        j--;
      }
      if (area > max_area) max_area = area;
    }
    return max_area;
  }
};

int main() {
  int a[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
  vector<int> height(a, a+sizeof(a)/sizeof(a[0]));
  int result = Solution().maxArea(height);
  cout << result << endl;
  return 0;
}
