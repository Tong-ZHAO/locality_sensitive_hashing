/******************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lshjaccard.h"

LSH_Jaccard::LSH_Jaccard(int dimension_feature, int num_hash_vector, int num_per_hash_vector):
              dim_feature(dimension_feature), 
              num_hash_vec(num_hash_vector),
              len_hash_vec(dim_feature/num_hash_vec),
              num_per_hash(num_per_hash_vector)
{
  assert(dim_feature == num_hash_vec * len_hash_vec);
  randomHashVector();

  for(int m = 0; m < num_hash_vec; m++){
    unordered_map<size_t, vector<int>> lsh_map;
    lsh_maps.push_back(lsh_map);
  }
}

void LSH_Jaccard::randomHashVector()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> rd_int(1, len_hash_vec);

  for(int m = 0; m < num_hash_vec * num_per_hash; m++){
    int vec_a = rd_int(gen);
    int vec_b = rd_int(gen);
    hash_vector.push_back(make_pair(vec_a, vec_b));
  }
}

void LSH_Jaccard::calBinaryFeature(double* feature, int* binary_feature)
{
  for(int m = 0; m < dim_feature; m++)
    binary_feature[m] = (fabs(feature[m]) < 0.00001 ? 0 : 1);
}

double LSH_Jaccard::calJaccardDistance(int* a, int* b, int len_vec)
{
  int num_intersection = 0, num_union = 0;
  for(int m = 0; m < len_vec; m++){
    num_intersection += ((a[m] + b[m] == 2)? 1 : 0);
    num_union += ((a[m] + b[m] == 0)? 0: 1);
  }
  return (1 - (double)num_intersection/(double)num_union);
}

size_t LSH_Jaccard::calHashKey(int* binary_feature, int hash_index)
{
  stringstream ostr;

  for(int n = 0; n < num_per_hash; n++){
    int index = dim_feature;
    for(int m = 0; m < len_hash_vec; m++){
      if(binary_feature[m + hash_index * len_hash_vec] == 1 && ((m * hash_vector[hash_index * num_per_hash + n].first + hash_vector[hash_index * num_per_hash + n].second) % hash_prime) % len_hash_vec < index)
        index = ((m * hash_vector[hash_index * num_per_hash + n].first + hash_vector[hash_index * num_per_hash + n].second) % hash_prime) % len_hash_vec;
    }

    ostr.fill(0);
    ostr.width(4);
    ostr << index;
  }

  string str1 = ostr.str();
  return str_hash(str1);
}

void LSH_Jaccard::updateHashMap(int* binary_feature, int feature_index)
{
  for(int m = 0; m < num_hash_vec; m++){
    size_t hash_key = calHashKey(binary_feature, m);
    lsh_maps[m][hash_key].push_back(feature_index);
  }
}

vector<int> LSH_Jaccard::searchInTable(int *bin_data)
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
