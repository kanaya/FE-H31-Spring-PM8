#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void Huffman(int &size, std::vector<int> &parent, std::vector<int> &left,
	     std::vector<int> &right, std::vector<int> freq) {
  void print_everything(const std::vector<int> &, const std::vector<int> &,
			const std::vector<int> &, const std::vector<int> &);
  void SortNode(int, const std::vector<int> &, const std::vector<int> &,
		int &, std::vector<int> &);
  std::vector<int> node(size);
  int nsize = 0;
  SortNode(size, parent, freq, nsize, node);
  print_everything(parent, left, right, freq);
  while (/* c */ nsize >= 2) {
    int i = node[0];
    int j = node[1];
    left[size] = i;
    right[size] = j;
    freq[size] = freq[i] + freq[j];
    parent[i] = size;
    parent[j] = size;
    size = size + 1;
    SortNode(size, parent, freq, nsize, node);
    print_everything(parent, left, right, freq);
  }
}

void SortNode(int size, const std::vector<int> &parent,
	      const std::vector<int> &freq, int &nsize,
	      std::vector<int> &node) {
  void Sort(const std::vector<int> &, int, std::vector<int> &);
  nsize = 0;
  for (int i = 0; i < size; i += 1) {
    if (/* d */ parent[i] < 0) {
      node[nsize] = i;
      nsize = nsize + 1;
    }
  }
  Sort(freq, nsize, node);
}

/* The following codes are not appeared in the question. */

bool operator <(const std::pair<int, int> &a,
		const std::pair<int, int> &b) {
  return a.first < b.first;
}

void Sort(const std::vector<int> &freq, int nsize, std::vector<int> &node) {
  std::vector<std::pair<int, int>> freq_and_node(nsize);

  auto fnm = freq_and_node.begin();
  auto f = freq.cbegin();
  auto n = node.cbegin();
  while (fnm != freq_and_node.end()) {
    *fnm = std::pair<int, int>(*f, *n);
    ++fnm;  ++f;  ++n;
  }
  std::sort(freq_and_node.begin(), freq_and_node.end());
  auto fn = freq_and_node.cbegin();
  auto nm = node.begin();
  while (fn != freq_and_node.cend()) {
    *nm = fn->second;
    ++nm;  ++fn;
  }
}

int idx(int c) {
  return c - 'A';
}

void init_freq(const std::string &s, int n, std::vector<int> &freq) {
  int l = s.length();
  for (int i = 0; i < l; ++i) {
    freq[i] = 0;
  }
  for (int i = 0; i < l; ++i) {
    int j = idx(s[i]);
    if (j < n) {
      freq[j] += 1;
    }
  }
}

std::ostream &operator <<(std::ostream &os, const std::vector<int> &a) {
  for (const auto &x: a) {
    os << std::setw(2) << std::right << x << " ";
  }
  return os;
}

void print_everything(const std::vector<int> &parent,
		      const std::vector<int> &left,
		      const std::vector<int> &right,
		      const std::vector<int> &freq) {
  std::cout << "parent: " << parent << std::endl;
  std::cout << "left:   " << left << std::endl;
  std::cout << "right:  " << right << std::endl;
  std::cout << "freq:   " << freq << std::endl;
  std::cout << "---" << std::endl;
}

int main(void) {
  int N = 4, N2 = N * N;
  std::string s { "AAAABBCDCDDACCAAAAA" };
  std::vector<int> parent(N2, -1), left(N2,  -1), right(N2, -1), freq(N2, -1);
  init_freq(s, N, freq);
  Huffman(N, parent, left, right, freq);
  return 0;
}
