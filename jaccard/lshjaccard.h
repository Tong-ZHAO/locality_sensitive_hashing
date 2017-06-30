/********************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Date: Dec 2016
 ********************************************************/

#include <random>
#include <unordered_map>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <assert.h>
#include <functional>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef LSHJACCARD_H
#define LSHJACCARD_H

class LSH_Jaccard{
public:
  LSH_Jaccard(int dimension_feature, int num_hash_vector, int num_per_hash_vector);

  void randomHashVector();
  void calBinaryFeature(double* feature, int* binary_feature);
  double calJaccardDistance(int* a, int* b, int len_vec);
  size_t calHashKey(int* binary_feature, int hash_index);
  void updateHashMap(int* binary_feature, int feature_index);

  vector<int> searchInTable(int *bin_data);

private:
  const int dim_feature;         // the dimension of each feature
  const int num_hash_vec;     // the number of hash vector
  const int len_hash_vec;     // the length of hash vector, it equals to dim_feature/num_hash_vec
  const int num_per_hash;
  const int hash_prime = 331;
  
  vector<pair<int, int>> hash_vector;  // hash vectors
  vector<unordered_map<size_t, vector<int>>> lsh_maps;         // hash table for the train dataset
  hash<string> str_hash;
};

#endif
