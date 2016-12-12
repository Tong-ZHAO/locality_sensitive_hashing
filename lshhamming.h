/********************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Date: Dec 2016
 ********************************************************/

#include <random>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef LSHHAMMING_H
#define LSHHAMMING_H

class LSH_Hamming{
public:
  LSH_Hamming(int dimension_feature, int max_feature_value, int num_hash_vector, int len_hash_vector);

  void randomHashVector();
  void calBinaryFeature(int* feature, int* binary_feature);
  size_t calHashKey(int* binary_feature, int hash_index);
  void updateHashMap(int* binary_feature, int feature_index);

  vector<int> searchInTable(int *data);

private:
  const int dim_feature;         // the dimension of each feature
  const int max_feature_val;     // the max possible value of feature
  const int num_hash_vec;     // the number of hash vectors
  const int len_hash_vec;     // the length of each hash vector
  const int dim_bit_feature;     // the length of each bit-value feature
  
  int **hash_vector;  // hash vectors
  unordered_map<size_t, vector<int>> lsh_map;         // hash table for the train dataset
  hash<string> str_hash;
};

#endif
