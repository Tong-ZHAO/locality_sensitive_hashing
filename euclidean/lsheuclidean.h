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
#include <functional>
#include <sstream>
#include <algorithm>

using namespace std;

#ifndef LSHEUCLIDEAN_H
#define LSHEUCLIDEAN_H

class LSH_Euclidean{
public:
  LSH_Euclidean(int dimension_feature, int number_hash_map, int number_per_map, int length_bucket, int hash_map_size);

  void randomHashVector();
  void calBinaryFeature(double* feature, int* binary_feature, int map_index);
  double calEuclideanDistance(double* a, double* b, int len_vec);
  int calHashKey1(int* binary_feature, int hash_index);
  int calHashKey2(int* binary_feature, int hash_index);
  void updateHashMap(double* feature, int feature_index);

  vector<int> searchInTable(double *data);

private:
  const int dim_feature;         // the dimension of each feature
  const int num_hash_map;     // the number of hash vector
  const int num_per_map;     // the number of each hash table
  const int len_bucket;       // the length of each bucket
  const int map_size;
  const int prime = 1 << 32 - 5;
  
  vector<int*> random_vec;        // a random vector to calculate hash function
  vector<vector<double*>> hash_vector;  // hash vectors
  vector<vector<double>> hash_bias;    // hash bias to calculate the projection
  unordered_map<int, unordered_map<int, vector<int>>> lsh_maps;         // hash table for the train dataset
  hash<string> str_hash;
};

#endif
