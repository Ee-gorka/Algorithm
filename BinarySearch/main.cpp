#include <iostream>
#include <vector>
int LowerBound(const std::vector<int> &v, const int &key) {
  int left = 0, right = (int) v.size() - 1;
  while (left < right) {
    int middle = (left + right) / 2;
    if (v[middle] >= key) right = middle;
    else left = middle + 1;
  }
  if (key > v[left]) return left + 1;
  return left;
}
int UpperBound(const std::vector<int> &v, const int &key) {
  int middle, left = 0, right = (int) v.size() - 1;
  while (left < right) {
    middle = (left + right) / 2;
    if (v[middle] <= key) left = middle + 1;
    else right = middle;
  }
  if (key >= v[left]) return left + 1;
  return left;
}
void BinarySearch(const std::vector<int> &v, int key, bool &flag) {
  int left = 0, right = (int) v.size() - 1, middle;
  while (!flag && left <= right) {
    middle = (left + right) / 2;
    if (v[middle] == key) flag = true;
    else if (v[middle] > key) right = middle - 1;
    else left = middle + 1;
  }
}

int main() {
  int n, k, right, left;
  bool flag = false;
  std::cin >> n;
  std::vector<int> array;
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    array.push_back(a);
  }
  std::cin >> k;
  for (int j = 0; j < k; ++j) {
    int key;
    std::cin >> key;
    BinarySearch(array, key, flag);
    left = LowerBound(array, key);
    right = UpperBound(array, key);
    std::cout << flag << " " << left << " " << right << '\n';
    flag = false;
  }
  return 0;
}