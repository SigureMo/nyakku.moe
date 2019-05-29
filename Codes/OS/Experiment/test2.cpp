#include <iostream>
#define INF 9999;

using namespace std;

typedef struct {
	char name;
	int arrival;
	int serve;
	int need;
	int start;
	int finish;
} process;

int N, T = 0;
bool is_finished(process *p);
void sort(process *p, string mode);
int FCFS(process *p, int index, bool &wait);
int RR(process *p, int index, bool &wait);
int SJF(process *p, int index, bool &wait);
int HRN(process *p, int index, bool &wait);
void print(process *p);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input scheduling algorithm and retry" << endl;
    return 1;
  }
  string mode = argv[1];
  cout << mode << endl;
	cin >> N;
	process p[N];
  int index = -1;
  bool wait = false;
	for (int i = 0; i < N; i++) {
		cin >> p[i].name >> p[i].arrival >> p[i].serve;
		p[i].need = p[i].serve;
		p[i].start = -1;
		p[i].finish = -1;
	}

  // pre-sort
  sort(p, mode); // 使用预排序以提高静态优先级查找速度

  // dispatch
  while (!is_finished(p)) {
    if (mode == "FCFS") {
      index = FCFS(p, index, wait);
    }
    else if (mode == "RR") {
      index = RR(p, index, wait);
    }
    else if (mode == "SJF") {
      index = SJF(p, index, wait);
    }
    else if (mode == "HRN") {
      index = HRN(p, index, wait);
    }
    T++;
    if (!wait) { // 是否没有新任务，若无则 CPU 空转
      p[index].need--;
      if (p[index].need == 0) {
        p[index].finish = T;
      }
    }
  }
  sort(p, "name");
  print(p);
	return 0;
}

bool is_finished(process *p) {
  for (int i = 0; i < N; i++) {
    if (p[i].need != 0) {
      return false;
    }
  }
  return true;
}

// input process array pointer and running process id and wait flag
// return new running process id
int FCFS(process *p, int index, bool &wait) {
  wait = false;
  if (index == -1 || p[index].need == 0) {
    if (p[index+1].arrival <= T) {
      index++;
      p[index].start = T;
    }
    else {
      wait = true;
    }
  }
  return index;
}

int RR(process *p, int index, bool &wait) {
  int cnt = 0;
  wait = false;
  while (true) {
    index = (index + 1) % N;
    if (p[index].need != 0 && p[index].arrival <= T) {
      if (p[index].start == -1) {
        p[index].start = T;
      }
      break;
    }
    if (cnt == N) {
      break;
    }
    cnt++;
  }
  if (cnt == N) wait = true;
  return index;
}

int SJF(process *p, int index, bool &wait) {
  wait = false;
  if (index == -1 || p[index].need == 0) {
    wait = true;
    for (int i = 0; i < N; i++) {
      if (p[i].need != 0 && p[i].arrival <= T) {
        index = i;
        p[index].start = T;
        wait = false;
        break;
      }
    }
  }
  return index;
}

int HRN(process *p, int index, bool &wait) {
  wait = false;
  float max = -INF;
  if (index == -1 || p[index].need == 0) {
    wait = true;
    for (int i = 0; i < N; i++) {
      if (p[i].need != 0 && p[i].arrival <= T) {
        float priority = (T - p[i].arrival) * 1.0 / p[i].serve;
        if (priority > max) {
          max = priority;
          wait = false;
          index = i;
          p[index].start = T;
        }
      }
    }
  }
  return index;
}

void sort(process *p, string mode) {
  process tmp;
  for (int i = N; i > 0; i--) {
    bool flag = false;
    for (int j = 0; j < i-1; j++) {
      if ((mode == "FCFS" || mode == "RR" || mode == "HRN") && (p[j].arrival > p[j+1].arrival) ||
          (mode == "SJF") && (p[j].serve > p[j+1].serve) ||
          (mode == "name") && (p[j].name > p[j+1].name)) {
        tmp = p[j];
        p[j] = p[j+1];
        p[j+1] = tmp;
        flag = true;
      }
    }
    if (flag == false) break;
  }
}

void print(process *p) {
  cout << "name\tarrival\tserve\tneed\tstart\tfinish\tTT\tQTT" << endl;
  float sum = 0;
  for (int i = 0; i < N; i++) {
    int TT = p[i].finish - p[i].arrival;
    float QTT = TT * 1.0 / p[i].serve;
    sum += QTT;
    cout << p[i].name << "\t" << p[i].arrival << "\t" << p[i].serve << "\t"
         << p[i].need << "\t" << p[i].start << "\t" << p[i].finish << "\t"
         << TT << "\t" << QTT << endl;
  }
  cout << "AQTT: " << sum / N << endl;
}
