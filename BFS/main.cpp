#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

void bfs(int t,
         int &size,
         int &c,
         std::vector<std::vector<int>> &g,
         std::vector<bool>& used,
         std::queue<int>& que,
         std::vector<int> &top_queue) {
  que.push(t);
  used[t] = true;
  while (!que.empty()) {
    int v = que.front();
    ++c;
    top_queue[v]=c;
    que.pop();
    for (size_t i = 0; i < size; ++i) {
      if (g[v][i] && !used[i]) {
        used[i] = true;
        que.push(i);
      }
    }
  }
}

int main() {
  std::ifstream input("input.txt");
  std::ofstream output("output.txt");
  int n, a, counter = 0;
  input >> n;
  std::vector<std::vector<int>> g(n);
  std::vector<bool> top_used(n);
  std::vector<int> top_queue(n);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      input >> a;
      g[i].push_back(a);
    }
  }
  std::queue<int> q_tops;
  for(int i = 0;i<n;++i){
    if(!top_used[i]){
      bfs(i,n,counter,g,top_used,q_tops,top_queue);

    }
  }
  for (int i = 0; i < n; ++i) {
    output << top_queue[i] << " ";
  }
  return 0;
}