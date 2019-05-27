#include <iostream>
#include <math.h>
#include <algorithm>
#define INF 999999

using namespace std;

int D = 0;
int maxIdx = -1, minIdx = INF;
int direct = 1;

int SSTF(int N, int S, bool* track);
int SCAN(int N, int S, bool* track);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input disk migration scheduling algorithm and retry" << endl;
    return 1;
  }
  bool track[INF] = {false};
  string mode = argv[1];
  cout << mode << endl;
  int N, S;
  cin >> N >> S;
  for (int i = 0; i < N; i++) {
    int tmp;
    cin >> tmp;
    if (tmp > maxIdx) maxIdx = tmp;
    if (tmp < minIdx) minIdx = tmp;
    track[tmp] = true;
  }
  for (int i = 0; i < N; i++) {
    if (mode == "SSTF") {
      S = SSTF(N, S, track);
    }
    else if (mode == "SCAN") {
      S = SCAN(N, S, track);
    }
  }
  cout << "distance " << D << " ave " << 1.0 * D / N << endl;
}

int SCAN(int N, int S, bool* track) {
  int i = S, dis;
  do {
    if (track[i]) {
      dis = abs(i - S);
      cout << i << " " << dis << endl;
      D += dis;
      track[i] = false;
      S = i;
      return S;
    }
    if (i >= maxIdx || i <= minIdx) direct = -direct;
    i += direct;
  } while (i >= minIdx && i <= maxIdx);
}

int SSTF(int N, int S, bool* track) {
  int left = S, right = S, dis, idx;
  while (!track[left] && left > minIdx-1) left--;
  while (!track[right] && right < maxIdx+1) right++;
  if (left < minIdx) left = -INF;
  if (right > maxIdx) right = INF;
  if (S - left < right - S) {
    dis = S - left;
    idx = left;
  }
  else {
    dis  = right - S;
    idx = right;
  }
  cout << idx << " " << dis << endl;
  D += dis;
  track[idx] = false;
  S = idx;
  return idx;
}
