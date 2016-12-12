/******************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lshhamming.h"
#include <vector>

LSH_Hamming::LSH_Hamming(int dimension_feature, int max_feature_value, int num_hash_vector, int len_hash_vector):
              dim_feature(dimension_feature), 
              max_feature_val(max_feature_value), 
              num_hash_vec(num_hash_vector), 
              len_hash_vec(len_hash_vector), 
              dim_bit_feature(max_feature_value * dimension_feature)
{
  hash_vector = new int*[num_hash_vec] ;
  for(int m = 0; m < num_hash_vec; m++)
    hash_vector[m] = new int[len_hash_vec];
  randomHashVector();
}

void LSH_Hamming::randomHashVector()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> rd_int(0, dim_bit_feature);

  for(int m = 0; m < num_hash_vec; m++)
    for(int n = 0; n < len_hash_vec; n++)
      hash_vector[m][n] = rd_int(gen);
}

void LSH_Hamming::calBinaryFeature(int* feature, int* binary_feature)
{
  for(int m = 0; m < dim_feature; m++)
    for(int n = 0; n < feature[m]; n++)
      binary_feature[m * max_feature_val + n] = 1;
}

size_t LSH_Hamming::calHashKey(int* binary_feature, int hash_index)
{
  stringstream ostr;
  for(int m = 0; m < dim_bit_feature; m++)
    ostr << binary_feature[hash_vector[hash_index][m]];

  string str1 = ostr.str();
  return str_hash(str1);
}

void LSH_Hamming::updateHashMap(int* binary_feature, int feature_index)
{
  for(int m = 0; m < num_hash_vec; m++){
    size_t hash_key = calHashKey(binary_feature, m);
    auto it = find(lsh_map[hash_key].begin(), lsh_map[hash_key].end(), feature_index);
    if(it == lsh_map[hash_key].end())
      lsh_map[hash_key].push_back(feature_index);
  }
}

vector<int> LSH_Hamming::searchInTable(int *data)
{
  vector<int> index_list;
  int *binary_feature = new int[dim_bit_feature] ();
  calBinaryFeature(data, binary_feature);

  for(int m = 0; m < num_hash_vec; m++){
    size_t hash_key = calHashKey(binary_feature, m);
    for(auto it = lsh_map[hash_key].begin(); it != lsh_map[hash_key].end(); it++)
      index_list.push_back(*it);
  }

  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());

  return index_list;
}
