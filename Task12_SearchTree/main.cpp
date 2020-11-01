#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
struct Node {
  long long key_value;
  std::vector<long long> length, tops;
  Node *left_;
  Node *right_;
  explicit Node(long long key_value = INT64_MAX,
                long long height = 0, long long left_height = 0, long long right_height = 0,
                std::vector<long long> length = {-1, -1, -1},
                std::vector<long long> tops = {-1, -1, -1},
                Node *left = nullptr,
                Node *right = nullptr)
      : key_value(key_value),
        length(std::move(length)),
        tops(std::move(tops)),
        left_(left),
        right_(right) {}
};

class BinaryTree {
 public:
  long long maxLength = -1;
  std::vector<std::pair<long long, long long>> Paths;
  Node rootPath;
  std::vector<long long> average;
  long long averageTop = INT64_MAX;
  bool nothingToDelete = false;
  BinaryTree();
  ~BinaryTree();
  void DestroyNode();
  void Insert(long long key);
  void Solution();
  void PreorderPrint(std::ostream &os);
  void DeleteNode(long long key);
 private:
  void Preorder(Node *node);
  void makeVector(Node *root, long long &key);
  long long findAverage(Node *node, std::vector<long long> &lv, std::vector<long long> &rv, const int &i, const int &j);
  void findMaxSemipath(Node *node,
                       std::vector<long long> &lh,
                       std::vector<long long> &lv,
                       std::vector<long long> &rh,
                       std::vector<long long> &rv, int c);
  static void PreorderPrint(std::ostream &os, Node *node);
  static void searchKey(Node *&current, long long key, Node *&parent);
  static Node *FindMinValue(Node *node);
  static void DestroyNode(Node *node);
  static void DeleteNode(Node *&node, long long key);
  static void Insert(long long key, Node *node);
  Node *root_;
};
BinaryTree::BinaryTree() {
  root_ = nullptr;
}
BinaryTree::~BinaryTree() {
  DestroyNode();
}
void BinaryTree::DestroyNode(Node *node) {

  if (node) {
    DestroyNode(node->left_);
    DestroyNode(node->right_);
    delete node;
  }

}
void BinaryTree::DestroyNode() {
  DestroyNode(root_);
}
void BinaryTree::Insert(long long key) {
  if (root_ != nullptr)
    Insert(key, root_);
  else {
    root_ = new Node;
    root_->key_value = key;
    root_->left_ = nullptr;
    root_->right_ = nullptr;
  }
}
void BinaryTree::Insert(long long key, Node *node) {
  if (key < node->key_value) {
    if (node->left_ != nullptr)
      Insert(key, node->left_);
    else {
      node->left_ = new Node;
      node->left_->key_value = key;
      node->left_->left_ = nullptr;
      node->left_->right_ = nullptr;
    }
  } else if (key > node->key_value) {
    if (node->right_ != nullptr)
      Insert(key, node->right_);
    else {
      node->right_ = new Node;
      node->right_->key_value = key;
      node->right_->left_ = nullptr;
      node->right_->right_ = nullptr;
    }
  }
}
void BinaryTree::PreorderPrint(std::ostream &os, Node *node) {
  if (node == nullptr) {
    return;
  }
  os << node->key_value << std::endl;
  PreorderPrint(os, node->left_);
  PreorderPrint(os, node->right_);
}
void BinaryTree::PreorderPrint(std::ostream &os) {
  PreorderPrint(os, root_);
}
Node *BinaryTree::FindMinValue(Node *node) {
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}
void BinaryTree::searchKey(Node *&current, long long key, Node *&parent) {
  while (current != nullptr && current->key_value != key) {
    parent = current;
    if (key < current->key_value)
      current = current->left_;
    else current = current->right_;
  }
}
void BinaryTree::DeleteNode(Node *&node, long long key) {
  Node *parent = nullptr;
  Node *current = node;
  searchKey(current, key, parent);
  if (current == nullptr) return;
  if (current->left_ == nullptr && current->right_ == nullptr) {
    if (current != node) {
      if (parent->left_ == current)
        parent->left_ = nullptr;
      else parent->right_ = nullptr;
    }
    free(current);
  } else if (current->left_ && current->right_) {
    Node *successor = FindMinValue(current->right_);
    long long val = successor->key_value;
    DeleteNode(node, successor->key_value);
    current->key_value = val;
  } else {
    Node *child = (current->left_) ? current->left_ : current->right_;
    if (current != node) {
      if (current == parent->left_)
        parent->left_ = child;
      else parent->right_ = child;
    } else node = child;
    free(current);
  }
}
void BinaryTree::DeleteNode(long long key) {
  DeleteNode(root_, key);
}
void BinaryTree::Solution() {
  Preorder(root_);
  if (!nothingToDelete) DeleteNode(averageTop);

}
void BinaryTree::Preorder(Node *node) {
  if (node == nullptr) {
    return;
  }
  std::vector<long long> lheight(3), rheight(3), lvalues(3), rvalues(3), nodheight(3), nodvalues(3);
  Preorder(node->left_);
  Preorder(node->right_);
  if (node->left_ == nullptr && node->right_ == nullptr)
    lheight = {-1, -1, -1}, lvalues = {-1, -1, -1}, rheight = {-1, -1, -1}, rvalues = {-1, -1, -1};
  else if (node->left_ == nullptr)
    lheight = {-1, -1, -1}, lvalues = {-1, -1, -1}, rheight = node->right_->length, rvalues = node->right_->tops;
  else if (node->right_ == nullptr)
    rheight = {-1, -1, -1}, rvalues = {-1, -1, -1}, lheight = node->left_->length, lvalues = node->left_->tops;
  else
    rheight = node->right_->length, rvalues = node->right_->tops, lheight = node->left_->length, lvalues =
        node->left_->tops;
  int NumberPreds;
  long long currentValue = node->key_value;
  if (node->left_ == nullptr && node->right_ == nullptr) NumberPreds = 0;
  else if (node->left_ != nullptr && node->right_ != nullptr) NumberPreds = 2;
  else NumberPreds = 1;
  for (int i = 0; i < 3; ++i) {
    long long newh, newv;
    if (lheight[i] == rheight[i]) {
      newv = lvalues[i] < rvalues[i] ? lvalues[i] : rvalues[i];
      if (lheight[i] == -1)newh = lheight[i];
      else newh = lheight[i] + 1;
    } else if (lheight[i] < rheight[i]) {
      newh = rheight[i] + 1;
      newv = rvalues[i];
    } else {
      newh = lheight[i] + 1;
      newv = lvalues[i];
    }
    if (newh == -1) {
      if (NumberPreds == i) {
        nodheight[i] = 0;
        nodvalues[i] = currentValue;
      } else {
        nodheight[i] = -1;
        nodvalues[i] = -1;
      }
    } else if (newh == 0) {
      nodheight[i] = newh + 1;
      nodvalues[i] = newv;
    } else {
      nodheight[i] = newh;
      nodvalues[i] = newv;
    }
  }
  node->length = nodheight;
  node->tops = nodvalues;
  std::vector<long long> newvalues(3, -1);
  std::vector<long long> newheight(3, -1);
  newheight[NumberPreds] = 0;
  newvalues[NumberPreds] = node->key_value;
  if (node->left_ != nullptr || node->right_ != nullptr) {
    if (node->left_ != nullptr && node->right_ != nullptr) {
      findMaxSemipath(node, lheight, lvalues, rheight, rvalues, 2);
      findMaxSemipath(node, lheight, lvalues, newheight, newvalues, 1);
      findMaxSemipath(node, newheight, newvalues, rheight, rvalues, 1);
    } else if (node->left_ != nullptr) findMaxSemipath(node, lheight, lvalues, newheight, newvalues, 1);
    else if (node->right_ != nullptr) findMaxSemipath(node, newheight, newvalues, rheight, rvalues, 1);
  }
}
void BinaryTree::makeVector(Node *root, long long &key) {
  if (root == nullptr) return;
  if (root->key_value == key) {
    average.push_back(root->key_value);
    return;
  }
  if (key < root->key_value) {
    makeVector(root->left_, key);
    average.push_back(root->key_value);
  } else {
    average.push_back(root->key_value);
    makeVector(root->right_, key);
  }
}

void BinaryTree::findMaxSemipath(Node *node,
                                 std::vector<long long> &lh,
                                 std::vector<long long> &lv,
                                 std::vector<long long> &rh,
                                 std::vector<long long> &rv, int c) {
  int firstTop = -1, secondTop = -1;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (lh[i] == -1 || rh[j] == -1 || i == j) continue;
      if (lh[i] + rh[j] + c > maxLength) {
        while (!Paths.empty()) Paths.pop_back();
        nothingToDelete = false;
        maxLength = lh[i] + rh[j] + c;
        rootPath = *node;
        averageTop = findAverage(node, lv, rv, i, j);
        if ((int) average.size() != 0) firstTop = lv[i], secondTop = rv[j];
        if (firstTop != -1 && secondTop != -1)Paths.emplace_back(firstTop, secondTop);
        continue;
      }
      if (lh[i] + rh[j] + c == maxLength) {
        if (lv[i] + rv[j] < Paths[0].first + Paths[0].second) {
          while (!Paths.empty()) Paths.pop_back();
          nothingToDelete = false;
          maxLength = lh[i] + rh[j] + c;
          rootPath = *node;
          averageTop = findAverage(node, lv, rv, i, j);
          if ((int) average.size() != 0) firstTop = lv[i], secondTop = rv[j];
          if (firstTop != -1 && secondTop != -1)Paths.emplace_back(firstTop, secondTop);
        } else if (lv[i] + rv[j] == Paths[0].first + Paths[0].second) {
          if (node->key_value < rootPath.key_value) {
            while (!Paths.empty()) Paths.pop_back();
            nothingToDelete = false;
            maxLength = lh[i] + rh[j] + c;
            rootPath = *node;
            averageTop = findAverage(node, lv, rv, i, j);
            if ((int) average.size() != 0) firstTop = lv[i], secondTop = rv[j];
            if (firstTop != -1 && secondTop != -1)Paths.emplace_back(firstTop, secondTop);
          } else if (node->key_value < rootPath.key_value) continue;
          else {
            while (!Paths.empty()) Paths.pop_back();
            long long currentAverage = findAverage(node, lv, rv, i, j);
            if (currentAverage != averageTop) nothingToDelete = true;
            else {
              nothingToDelete = false;
              maxLength = lh[i] + rh[j] + c;
              rootPath = *node;
              if ((int) average.size() != 0) firstTop = lv[i], secondTop = rv[j];
              if (firstTop != -1 && secondTop != -1)Paths.emplace_back(firstTop, secondTop);
            }
          }
        }
      }
    }
  }
}
long long BinaryTree::findAverage(Node *node,
                                  std::vector<long long> &lv,
                                  std::vector<long long> &rv,
                                  const int &i,
                                  const int &j) {
  average.clear();
  if (node->left_ != nullptr && node->right_ != nullptr) {
    makeVector(node, lv[i]);
    average.pop_back();
    makeVector(node, rv[j]);
  } else if (node->left_ != nullptr && node->right_ == nullptr) {
    average.clear();
    makeVector(node, lv[i]);
  } else if (node->right_ != nullptr && node->left_ == nullptr) {
    average.clear();
    makeVector(node, rv[j]);
  }
  if (average.size() % 2 == 0) return -1;
  else return average[(average.size() - 1) / 2];
}
int main() {
  BinaryTree tree;
  std::ifstream in("tst.txt");
  std::ofstream out("tst1.txt");
  long long peak;
  while (in >> peak) {
    tree.Insert(peak);
  }
  tree.Solution();
  tree.PreorderPrint(out);
  return 0;
}