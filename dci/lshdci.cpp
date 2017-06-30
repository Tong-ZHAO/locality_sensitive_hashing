/******************************************************
 * Basic class to use locality hash functions
 * Author: Tong ZHAO
 * Data: Fev 2017
 *******************************************************/

#include "lshdci.h"

LSH_Dci::LSH_Dci(int dimension_feature, int length_vector, int number_vector, int max_number):
              dim_feature(dimension_feature), 
              len_vector(length_vector), 
              num_vector(number_vector),
              max_num(max_number)
{
  for(int i = 0; i < num_vector; i++){
    vector<int> vec;
    hash_vector.push_back(vec);
    for(int j = 0; j < len_vector; j++){
      vector<pair<double, int>> proj;
      hash_table.push_back(proj);
    }
  }

  randomHashVector();
}

void LSH_Dci::randomHashVector()
{
  for(int m = 0; m < num_vector; m++){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> rd_int(0, dim_feature);
    for(int n = 0; n < len_vector; n++)
      hash_vector[m].push_back(rd_int(gen));
  }
}

double LSH_Dci::calEuclideanDistance(double* a, double* b, int len_vec)
{
  double distance = 0;
  for(int m = 0; m < len_vec; m++)
    distance += pow(a[m] - b[m], 2);
  return sqrt(distance);
}

void LSH_Dci::updateHashMap(double* feature, int feature_index)
{
  for(int m = 0; m < num_vector; m++){
    for(int n = 0; n < len_vector; n++)
      hash_table[m * len_vector + n].push_back(make_pair(*(feature + hash_vector[m][n]), feature_index));
  }
}

void LSH_Dci::sortHashMap(vector<pair<double, int>> &sort_list)
{
  auto cmp = [](pair<double, int> const &a, pair<double, int> const &b){
    if(a.first < b.first) return true;
    else if(a.first == b.first) return a.second < b.second;
    else return false;
    //return a.first < b.first;
  };

  sort(sort_list.begin(), sort_list.end(), cmp);
}

vector<int> LSH_Dci::searchInTable(double *data)
{
  vector<int> index_list;
  int num_point = hash_table[0].size();
  vector<vector<pair<double, int>>> tmp_table;

  for(int i = 0; i < num_vector * len_vector; i++){
    vector<pair<double, int>> tmp_vec;
    double proj = *(data + hash_vector[i/len_vector][i%len_vector]);
    for(int j = 0; j < num_point; j++)
      tmp_vec.push_back(make_pair(fabs(hash_table[i][j].first - proj), hash_table[i][j].second));
      
    sortHashMap(tmp_vec);
    tmp_table.push_back(tmp_vec);
  }

  int index = 0;
  vector<vector<int>> counter;
  for(int i = 0; i < num_vector; i++){
    vector<int> tmp_counter;
    for(int j = 0; j < num_point; j++)
      tmp_counter.push_back(0);
    counter.push_back(tmp_counter);
  }

  while(index_list.size() < max_num){
    for(int l = 0; l < num_vector; l++){
      vector<int> min_indexes;
      for(int j = 0; j < len_vector; j++){
        counter[l][tmp_table[l * len_vector + j][index].second] += 1;
        min_indexes.push_back(tmp_table[l * len_vector + j][index].second);
      }
      for(int j = 0; j < len_vector; j++)
        if(counter[l][min_indexes[j]] == len_vector &&
          find(index_list.begin(), index_list.end(), min_indexes[j]) == index_list.end()) 
          index_list.push_back(min_indexes[j]);
    }
    index++;
  }
      
  return index_list;
}
