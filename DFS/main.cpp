#include <iostream>
#include <vector>
#include <fstream>

void dfs(int t,
         std::vector<bool> &used,
         std::vector<std::vector<int>> &graph,
         std::vector<int> &queue,
         int &c,
         int &size) {
  c++;
  used[t] = 1;
  queue[t] = c;
  for (int i = 0; i < size; ++i) {
    if (graph[t][i] && !used[i]) {
      dfs(i, used, graph, queue, c, size);
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
  dfs(0, top_used, g, top_queue, counter, n);
  for(int i =0 ; i < n; ++i){
    if(top_queue[i]==0){
      dfs(i, top_used, g, top_queue, counter, n);
        }
      }
  for (int i = 0; i < n; ++i) {
    output << top_queue[i] << " ";
  }
  return 0;
}
