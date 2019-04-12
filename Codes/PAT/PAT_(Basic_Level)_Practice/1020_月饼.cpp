#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
  float inventory;
  float price;
};

bool cmp(struct node& n1, struct node& n2);

int main() {
  int N;
  float need;
  vector<struct node> v;
  cin >> N >> need;
  for (int i = 0; i < N; i++) {
    struct node n;
    cin >> n.inventory;
    v.push_back(n);
  }
  for (int i = 0; i < N; i++) {
    cin >> v[i].price;
  }
  sort(v.begin(), v.end(), cmp);
  float earnings = 0;
  for (int i = 0; i < v.size() && need > 0; i++) {
    if (need >= v[i].inventory) {
      earnings += v[i].price;
      need -= v[i].inventory;
    }
    else {
      earnings += need / v[i].inventory * v[i].price;
      need = 0;
    }
  }
  printf("%.2f", earnings);
  return 0;
}

bool cmp(struct node& n1, struct node& n2) {
  return n1.price / n1.inventory > n2.price / n2.inventory;
}
