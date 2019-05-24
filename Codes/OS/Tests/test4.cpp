#include <iostream>
#include <math.h>
#include <algorithm>
#define INF 999999

using namespace std;

int D = 0;

void SSTF(int N, int S, int* track_nums, bool* flags);
void SCAN(int N, int S, int* track_nums, bool* flags);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input disk migration scheduling algorithm and retry" << endl;
    return 1;
  }
  string mode = argv[1];
  cout << mode << endl;
  int N, S;
  cin >> N >> S;
  int track_nums[N];
  bool flags[N] = {false};
  for (int i = 0; i < N; i++) {
    cin >> track_nums[i];
  }
  sort(track_nums, track_nums + N);
  if (mode == "SSTF") {
    SSTF(N, S, track_nums, flags);
  }
  else if (mode == "SCAN") {
    SCAN(N, S, track_nums, flags);
  }
  cout << "distance " << D << " ave " << 1.0 * D / N << endl;
}

void SSTF(int N, int S, int* track_nums, bool* flags) {
  int i = 0;
  int left, right;
  int left_dis, right_dis;
  while (i < N && track_nums[i] < S) i++;
  if (S == track_nums[i]) {
    cout << S << " " << 0 << endl;
    flags[i] = true;
  }
  left = i - 1;
  right = i;
  while (left >= 0 || right < N) {
    if (left < 0) left_dis = INF;
    else left_dis = S - track_nums[left];
    if (right >= N) right_dis = INF;
    else right_dis = track_nums[right] - S;
    if (left_dis < right_dis) {
      cout << track_nums[left] << " " << left_dis << endl;
      D += left_dis;
      flags[left] = true;
      S = track_nums[left];
      do {
        left--;
      } while (left >= 0 && flags[left]);
    }
    else {
      cout << track_nums[right] << " " << right_dis << endl;
      D += right_dis;
      flags[right] = true;
      S = track_nums[right];
      do {
        right++;
      } while (right < N && flags[right]);
    }
  }
}

void SCAN(int N, int S, int* track_nums, bool* flags) {
  int i = 0;
  int direct = 1, dis;
  while (i < N && track_nums[i] < S) i++;
  for (; i >= 0; i += direct) {
    if (i == N) {
      direct = -direct;
      continue;
    }
    if (!flags[i]) {
      dis = abs(track_nums[i] - S);
      cout << track_nums[i] << " " << dis << endl;
      D += dis;
      flags[i] = true;
      S = track_nums[i];
    }
  }
}
