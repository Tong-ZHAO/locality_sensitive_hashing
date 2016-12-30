/******************************************************
 * Basic class to use locality hash functions with hamming distance
 * Author: Tong ZHAO
 * Data: Dec 2016
 *******************************************************/

#include "lshcosine.h"

using namespace std;

LSH_Cosine::LSH_Cosine(int dimension_feature, int num_hash_vector):
    dim_feature(dimension_feature),
    num_hash_vec(num_hash_vector)
{
  // initialize a num_hash_vec*dim_feature matrix to store hash vectors
  hash_vector = new double* [num_hash_vec];
  for(int m = 0; m < num_hash_vec; m++)
    hash_vector[m] = new double[dim_feature];

  /* initialize the vector of lsh maps
  for(int n = 0; n < num_hash_vec; n++){
    unordered_map<size_t, vector<int>> lsh_map;
    lsh_maps.push_back(lsh_map);
  }*/

  randomHashVector();
}

void LSH_Cosine::randomHashVector()
{
  ofstream outfile("/home/xt/tong/mopsi/locality_sensitive_hashing/data/hash_vec.csv");
  // make each vector to be a normalized distribution
  for(int m = 0; m < num_hash_vec; m++){
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> distribution(0.0, 1.0);
    for(int n = 0; n < dim_feature; n++){
      hash_vector[m][n] = distribution(gen);
      // write file
      outfile << hash_vector[m][n] << ",";
    }
    outfile << endl;
  }
  outfile.close();
}

double LSH_Cosine::cosine_similarity(double* A, double* B, int len_vec)
{
  double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
  for(int m = 0; m < len_vec; m++){
    dot += A[m] * B[m];
    denom_a += A[m] * A[m];
    denom_b += B[m] * B[m];
  }
  return dot / (sqrt(denom_a) * sqrt(denom_b));
}

void LSH_Cosine::calBinaryFeature(double* feature, int* binary_feature)
{
  for(int m = 0; m < num_hash_vec; m++){
    double dot = cosine_similarity(feature, hash_vector[m], dim_feature);
    binary_feature[m] = (dot > 0.0) ? 1: 0;
  }
}

size_t LSH_Cosine::calHashKey(int* binary_feature)
{
  stringstream ostr;
  for(int m = 0; m < num_hash_vec; m++)
    ostr << binary_feature[m];

  string str1 = ostr.str();
  return str_hash(str1);
}

void LSH_Cosine::updateHashMap(int* binary_feature, int feature_index)
{
  size_t hash_key = calHashKey(binary_feature);
  //cout << hash_key << endl;
  lsh_map[hash_key].push_back(feature_index);
}

vector<int> LSH_Cosine::searchInTable(int *data)
{
  size_t hash_key = calHashKey(data);
  return lsh_map[hash_key];
}
