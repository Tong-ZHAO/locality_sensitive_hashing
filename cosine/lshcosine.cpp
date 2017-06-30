/******************************************************
 * Basic class to use locality hash functions with hamming distance
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lshcosine.h"

using namespace std;

LSH_Cosine::LSH_Cosine(int dimension_feature, int number_hash_vector, int number_hash_map):
    dim_feature(dimension_feature),
    num_hash_vec(number_hash_vector),
    num_hash_map(number_hash_map)
{
  // initialize a matrix whose length equal to num_hash_vec*dim_feature matrix to store hash vectors
  for(int m = 0; m < num_hash_map; m++){
    unordered_map<size_t, vector<int>> tmp_map;
    lsh_map.push_back(tmp_map);

    vector<double*> tmp_vec;    
    for(int n = 0; n < num_hash_vec; n++){
      double* vec = new double[dim_feature];
      tmp_vec.push_back(vec);
    }
    hash_vector.push_back(tmp_vec);
  }
  randomHashVector();
}

void LSH_Cosine::randomHashVector()
{
  // make each vector to be a normalized distribution
  for(int m = 0; m < num_hash_map; m++){
    for(int n = 0; n < num_hash_vec; n++){
      random_device rd;
      mt19937 gen(rd());
      normal_distribution<double> distribution(0.0, 1.0);
      for(int i = 0; i < dim_feature; i++)
        hash_vector[m][n][i] = distribution(gen);
    }
  }
}

double LSH_Cosine::cosine_similarity(double* A, double* B, int len_vec)
{
  // calculate cosine similarity
  double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
  for(int m = 0; m < len_vec; m++){
    dot += A[m] * B[m];
    denom_a += A[m] * A[m];
    denom_b += B[m] * B[m];
  }
  return dot / (sqrt(denom_a) * sqrt(denom_b));
}

void LSH_Cosine::calBinaryFeature(double* feature, int* binary_feature, int index)
{
  // calculate original hash key
  for(int m = 0; m < num_hash_vec; m++){
    double dot = cosine_similarity(feature, hash_vector[index][m], dim_feature);
    binary_feature[m] = (dot > 0.0) ? 1: 0;
  }
}

size_t LSH_Cosine::calHashKey(int* binary_feature)
{
  // tranform original hash key to C++ hash key
  // (to make sure that the key is not bigger than the limit of int)
  stringstream ostr;
  for(int m = 0; m < num_hash_vec; m++)
    ostr << binary_feature[m];

  string str1 = ostr.str();
  return str_hash(str1);
}

void LSH_Cosine::updateHashMap(double* feature, int feature_index)
{
  // add a feature to train dataset
  for(int m = 0; m < num_hash_map; m++){
    int* bin_feature = new int[num_hash_vec];
    calBinaryFeature(feature, bin_feature, m);
    size_t hash_key = calHashKey(bin_feature);
    lsh_map[m][hash_key].push_back(feature_index);
    delete [] bin_feature;
  }
}

vector<int> LSH_Cosine::searchInTable(double *data)
{
  // search candidate points in train dataset
  vector<int> index_list;

  for(int m = 0; m < num_hash_map; m++){
    int* bin_data = new int[num_hash_vec];
    calBinaryFeature(data, bin_data, m);
    size_t hash_key = calHashKey(bin_data);
    delete [] bin_data;

    for(auto it = lsh_map[m][hash_key].begin(); it != lsh_map[m][hash_key].end(); it++)
      index_list.push_back(*it);
  }

  // delete repeated elements
  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());
 
  return index_list;
}
