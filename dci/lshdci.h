/********************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Date: Fev 2017
 ********************************************************/

#include <random>
#include <math.h>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

#ifndef LSHDCI_H
#define LSHDCI_H

class LSH_Dci{
public:
  LSH_Dci(int dimension_feature, int length_vector, int number_vector, int max_number);

  void randomHashVector();
  double calEuclideanDistance(double* a, double* b, int len_vec);
  void updateHashMap(double* feature, int feature_index);
  void sortHashMap(vector<pair<double, int>> &sort_list);

  vector<int> searchInTable(double *data);

private:
  const int dim_feature;         // the dimension of each feature
  const int len_vector;     // the number of hash vector
  const int num_vector;     // the number of each hash table
  const int max_num; 
  
  vector<vector<int>> hash_vector;  // hash vectors
  vector<vector<pair<double, int>>> hash_table;    // hash tables 
};

#endif
