#include <iostream>
#include <vector>
#include<algorithm>

using namespace std;

vector<int> cover_nums;
vector<int> key_nums;

bool is_covered(int num);
void check_num(int num);
bool compare(const int &v1, const int &v2);

int main() {
  int n;
  cin >> n;
  int nums[n];
  for (int i = 0; i < n; i++) {
    int num;
    cin >> num;
    nums[i] = num;
    check_num(num);
  }
  for (int i = 0; i < sizeof(nums) / sizeof(nums[0]); i++) {
    if (!is_covered(nums[i])) {
      key_nums.push_back(nums[i]);
    }
  }
  sort(key_nums.begin(), key_nums.end(), compare);
  for (int i = 0; i < key_nums.size(); i++) {
    if (i != 0) {
      cout << " ";
    }
    cout << key_nums[i];
  }
  return 0;
}

void check_num(int num) {
  bool first = true;
  while (num > 1) {
    if (first) {
      first = false;
    }
    else {
      if (is_covered(num)) {
        return;
      }
      else {
        cover_nums.push_back(num);
      }
    }
    if (num % 2 == 0) {
      num = num / 2;
    }
    else {
      num = (3 * num + 1) / 2;
    }
  }
}

bool is_covered(int num) {
  for (int i = 0; i < cover_nums.size(); i++) {
    if (cover_nums[i] == num) {
      return true;
    }
  }
  return false;
}

bool compare(const int &v1, const int &v2) {
  return v1 > v2;
}
