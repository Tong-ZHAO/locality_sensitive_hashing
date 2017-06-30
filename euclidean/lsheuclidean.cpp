/******************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lsheuclidean.h"

LSH_Euclidean::LSH_Euclidean(int dimension_feature, int number_hash_map, int number_per_map, int length_bucket,  int hash_map_size):
              dim_feature(dimension_feature), 
              num_hash_map(number_hash_map), 
              num_per_map(number_per_map),
              len_bucket(length_bucket),
              map_size(hash_map_size)
{
  for(int i = 0; i < num_hash_map; i++){
    vector<double*> vec;
    hash_vector.push_back(vec);

    vector<double> bias;
    hash_bias.push_back(bias);
  }

  randomHashVector();
}

void LSH_Euclidean::randomHashVector()
{
  for(int m = 0; m < num_hash_map; m++){
    for(int n = 0; n < num_per_map; n++){
      random_device rd;
      mt19937 gen(rd());
      uniform_int_distribution<int> rd_int(0, len_bucket);
      normal_distribution<double> distribution(0.0, 1.0);

      double* hash_vec = new double[dim_feature];
      for(int i = 0; i < dim_feature; i++)
        hash_vec[i] = distribution(gen);
      
      hash_vector[m].push_back(hash_vec);
      hash_bias[m].push_back(rd_int(gen));
    }
  }

  for(int k = 0; k < 2 * num_hash_map; k++){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rd_int(0, dim_feature);
    int* hash_vec = new int[num_per_map];

    for(int i = 0; i < num_per_map; i++)
      hash_vec[i] = rd_int(gen);

    random_vec.push_back(hash_vec);
  }
}

void LSH_Euclidean::calBinaryFeature(double* feature, int* binary_feature, int map_index)
{
  for(int i = 0; i < num_per_map; i++){
    double result = 0.0;
    for(int m = 0; m < dim_feature; m++)
      result += feature[m] * hash_vector[map_index][i][m];
    binary_feature[i] = (int)((result + hash_bias[map_index][i]) / (double)len_bucket);
  }
}

double LSH_Euclidean::calEuclideanDistance(double* a, double* b, int len_vec)
{
  double distance = 0;
  for(int m = 0; m < len_vec; m++)
    distance += pow(a[m] - b[m], 2);
  return sqrt(distance);
}

int LSH_Euclidean::calHashKey1(int* binary_feature, int hash_index)
{
  int result = 0;

  for(int m = 0; m < num_per_map; m++)
    result += binary_feature[m] * random_vec[hash_index * 2][m]; 

  return ((result % prime) % map_size);
}

int LSH_Euclidean::calHashKey2(int* binary_feature, int hash_index)
{
  int result = 0;

  for(int m = 0; m < num_per_map; m++)
    result += binary_feature[m] * random_vec[hash_index * 2 + 1][m];

  return (result % prime);
}

void LSH_Euclidean::updateHashMap(double* feature, int feature_index)
{
  for(int m = 0; m < num_hash_map; m++){
    int* bin_feature = new int[num_per_map];
    calBinaryFeature(feature, bin_feature, m);
    int hash_key_1 = calHashKey1(bin_feature, m);
    int hash_key_2 = calHashKey2(bin_feature, m);
    lsh_maps[hash_key_1][hash_key_2].push_back(feature_index);
  }
}

vector<int> LSH_Euclidean::searchInTable(double *data)
{
  vector<int> index_list;

  for(int m = 0; m < num_hash_map; m++){
    int* bin_data = new int[num_per_map];
    calBinaryFeature(data, bin_data, m);
    int hash_key_1 = calHashKey1(bin_data, m);
    int hash_key_2 = calHashKey2(bin_data, m);

    for(auto it = lsh_maps[hash_key_1][hash_key_2].begin(); it != lsh_maps[hash_key_1][hash_key_2].end(); it++)
      index_list.push_back(*it);
  }

  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());

  return index_list;
}
