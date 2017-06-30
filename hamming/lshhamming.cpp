/******************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lshhamming.h"

LSH_Hamming::LSH_Hamming(int dimension_feature, int num_hash_vector, int len_hash_vector):
              dim_feature(dimension_feature), 
              num_hash_vec(num_hash_vector), 
              len_hash_vec(len_hash_vector) 
{
  hash_vector = new int*[num_hash_vec];
  for(int m = 0; m < num_hash_vec; m++)
    hash_vector[m] = new int[len_hash_vec];
  randomHashVector();

  for(int n = 0; n < num_hash_vec; n++){
    unordered_map<size_t, vector<int>> lsh_map;
    lsh_maps.push_back(lsh_map);
  }
}

void LSH_Hamming::randomHashVector()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> rd_int(0, dim_feature);

  for(int m = 0; m < num_hash_vec; m++)
    for(int n = 0; n < len_hash_vec; n++)
      hash_vector[m][n] = rd_int(gen);
}

void LSH_Hamming::calBinaryFeature(double* feature, int* binary_feature)
{
  for(int m = 0; m < dim_feature; m++)
    binary_feature[m] = (fabs(feature[m]) < 0.001 ? 0 : 1);
}

int LSH_Hamming::calHammingDistance(int* a, int* b, int len_vec)
{
  int distance = 0;
  for(int m = 0; m < len_vec; m++)
    distance += ((a[m] == b[m])? 0 : 1);
  return distance;
}

size_t LSH_Hamming::calHashKey(int* binary_feature, int hash_index)
{
  stringstream ostr;
  for(int m = 0; m < len_hash_vec; m++)
    ostr << binary_feature[hash_vector[hash_index][m]];

  string str1 = ostr.str();
  return str_hash(str1);
}

void LSH_Hamming::updateHashMap(int* binary_feature, int feature_index)
{
  for(int m = 0; m < num_hash_vec; m++){
    size_t hash_key = calHashKey(binary_feature, m);
    lsh_maps[m][hash_key].push_back(feature_index);
  }
}

vector<int> LSH_Hamming::searchInTable(int *bin_data)
{
  vector<int> index_list;

  for(int m = 0; m < num_hash_vec; m++){
    size_t hash_key = calHashKey(bin_data, m);
    for(auto it = lsh_maps[m][hash_key].begin(); it != lsh_maps[m][hash_key].end(); it++)
      index_list.push_back(*it);
  }

  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());

  return index_list;
}
