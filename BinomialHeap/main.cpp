#include <cmath>
#include <fstream>
#include <vector>
int main() {
  std::ifstream in("input.txt");
  std::ofstream out("output.txt");
  long long n,nn, bn, ans = 0;
  std::vector<long long> answer;
  in >> n;
  nn=n;
  while (nn) {
    answer.push_back(nn % 2);
    nn /= 2;
  }
  for (int i = 0; i < (int) answer.size(); ++i) {
    if (answer[i] != 0) {
      ans += pow(2, i);
    }
  }
  if (ans != n) {
    out << -1;
    return 0;
  } else {
    for (int i = 0; i < (int) answer.size(); ++i) {
      if (answer[i] != 0) out << i << std::endl;
    }
    return 0;
  }

}