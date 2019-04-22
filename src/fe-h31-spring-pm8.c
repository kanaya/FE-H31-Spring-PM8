#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* The following macro is not appeared in the question. */
#define FREE_IF_NOT_NULL(p) ((p) ? (free((p)), (p) = NULL) : NULL)

/* The following two functions are for showing internal statuses. */
void print_int_array(int a[], int n) {
  int i;
  for (i = 0; i < n; ++i) {
    printf("%4d ", a[i]);
  }
}

void print_everything(int parent[], int left[], int right[], int freq[], int n) {
  printf("parent: "); print_int_array(parent, n); printf("\n");
  printf("left:   "); print_int_array(left, n);   printf("\n");
  printf("right:  "); print_int_array(right, n);  printf("\n");
  printf("freq:   "); print_int_array(freq, n);   printf("\n");
  printf("---\n");
}

void Huffman(int *size, int parent[], int left[], int right[], int freq[]) {
  void SortNode(int, const int [], const int [], int *, int []);
  int i, j, nsize;
  int *node;

  assert(node = (int *)malloc(sizeof(int) * *size));
  SortNode(*size, parent, freq, &nsize, node);
  print_everything(parent, left, right, freq, *size);
  while (/* c */ nsize >= 2) {
    i = node[0];
    j = node[1];
    left[*size] = i;
    right[*size] = j;
    freq[*size] = freq[i] + freq[j];
    parent[i] = *size;
    parent[j] = *size;
    *size = *size + 1;
    SortNode(*size, parent, freq, &nsize, node);
    print_everything(parent, left, right, freq, *size);
  }
  FREE_IF_NOT_NULL(node);
}

void SortNode(int size, const int parent[], const int freq[], int *nsize, int node[]) {
  void Sort(const int [], int, int *);
  int i;

  *nsize = 0;
  for (i = 0; i < size; i += 1) {
    if (/* d */ parent[i] < 0) {
      node[*nsize] = i;
      *nsize = *nsize + 1;
    }
  }
  Sort(freq, *nsize, node);
}

/* The following codes are not appeared in the question. */

struct freq_and_node_t {
  int freq;
  int node;
};

typedef struct freq_and_node_t FREQ_AND_NODE_T;

int cmpr_freq_and_node(const void *a, const void *b) {
  int x = ((FREQ_AND_NODE_T *)a)->freq;
  int y = ((FREQ_AND_NODE_T *)b)->freq;
  return (x < y) ? -1 : ((x == y) ? 0 : 1);
}

void Sort(const int freq[], int nsize, int node[]) {
  FREQ_AND_NODE_T *freq_and_node;
  int i;

  assert(freq_and_node = (FREQ_AND_NODE_T *)malloc(sizeof(FREQ_AND_NODE_T) * nsize));
  for (i = 0; i < nsize; ++i) {
    freq_and_node[i].freq = freq[i];
    freq_and_node[i].node = node[i];
  }
  qsort((void *)freq_and_node, nsize, sizeof(FREQ_AND_NODE_T), cmpr_freq_and_node);
  for (i = 0; i < nsize; ++i) {
    node[i] = freq_and_node[i].node;
  }
  FREE_IF_NOT_NULL(freq_and_node);
}

int idx(int c) {
  return c - 'A';
}

void init_freq(const char s[], int len, int n, int freq[]) {
  int i;
  for (i = 0; i < len; ++i) {
    int j = idx(s[i]);
    if (j < n) {
      freq[j] += 1;
    }
  }
}

/* We assume that we only use A, B, C, and D. */
#define N  4
#define N2 (N * N)

int main(void) {
  const char s[] = "AAAABBCDCDDACCAAAAA";
  int *parent, *left, *right, *freq;
  int size, i;

  assert(parent = (int *)malloc(sizeof(int) * N2));
  assert(left = (int *)malloc(sizeof(int) * N2));
  assert(right = (int *)malloc(sizeof(int) * N2));
  assert(freq = (int *)malloc(sizeof(int) * N2));
  for (i = 0; i < N2; ++i) {
    parent[i] = left[i] = right[i] = -1;
    freq[i] = 0;
  }
  init_freq(s, strlen(s), N, freq);
  size = N;
  Huffman(&size, parent, left, right, freq);
  FREE_IF_NOT_NULL(parent);
  FREE_IF_NOT_NULL(left);
  FREE_IF_NOT_NULL(right);
  FREE_IF_NOT_NULL(freq);
  return 0;
}
