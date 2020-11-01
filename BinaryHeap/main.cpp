#include <iostream>
#include <fstream>
#include <vector>
int main() {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  std::vector<int> Heap;
  int n;
  in >> n;
  Heap.resize(n + 1);
  for (int i = 1; i < n + 1; ++i) {
    int a;
    in >> a;
    Heap[i] = a;
  }
  for (int j = 1; j < n + 1; ++j) {
    if (2 * j <= n) {
      if (Heap[2 * j] < Heap[j]) {
        out << "NO";
        return 0;
      }
    }
    if (2 * j + 1 <= n) {
      if (Heap[2 * j + 1] < Heap[j]) {
        out << "NO";
        return 0;
      }
    }
  }
  out << "YES";
  return 0;
}