/********************************************************
 * Basic class to use locality hash functions with cosine distance
 * Author: Tong ZHAO
 * Date: Dec 2016
 ********************************************************/

#include <random>
#include <unordered_map>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;

#ifndef LSHCOSINE_H
#define LSHCOSINE_H

class LSH_Cosine{
public:
  LSH_Cosine(int dimension_feature, int num_hash_vector);
  
  void randomHashVector();
  double cosine_similarity(double* A, double* B, int len_vec);
  void calBinaryFeature(double* feature, int* binary_feature);
  size_t calHashKey(int* binary_feature);
  void updateHashMap(int* binary_feature, int feature_index);

  vector<int> searchInTable(int *data);

private:
  const int dim_feature;         // the dimension of each feature
  const int num_hash_vec;        // the number of hash vectors

  double **hash_vector;          // hash vectors
  //vector<unordered_map<size_t, vector<int>>> lsh_maps;         
  unordered_map<size_t, vector<int>> lsh_map; // a vector of hash tables for the train dataset
  hash<string> str_hash;
};

#endif

