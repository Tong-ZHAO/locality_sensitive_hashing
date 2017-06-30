#include "lshhamming.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

const int feature_dim = 4096;
const int num_hash_vec = 8;
const int len_hash_vec = 8;

int main()
{
  LSH_Hamming hamming(feature_dim, num_hash_vec, len_hash_vec);
  vector<int*> train_data;
  vector<int*> val_data;
  
  //ifstream file("/home/xt/tong/mopsi/feature/imagenet_20_feature.txt");
  ifstream val_file("/home/xt/tong/mopsi/feature/keras/files/t20000_val_feature.txt");
  ifstream train_file("/home/xt/tong/mopsi/feature/keras/files/t20000_feature.txt");
  string line;

  while(train_file.good()){
    double *feature = new double[feature_dim];
    int index = 0;

    getline(train_file, line);
    if(line.length() < feature_dim) break;
    istringstream iss(line);

    while(iss.good()){
      double value;
      iss >> value;
      feature[index++] = value;
    }

    int *bin_feature = new int[feature_dim];
    hamming.calBinaryFeature(feature, bin_feature);
    train_data.push_back(bin_feature);
    delete [] feature;
  }

  cout << "The number of features: " << train_data.size() << endl;

  for(int n = 0; n < train_data.size(); n++)
    hamming.updateHashMap(train_data[n], n);
 
  while(val_file.good()){
    double *val_feature = new double[feature_dim];
    int index = 0;

    getline(val_file, line);
    if(line.length() < feature_dim) break;
    istringstream iss(line);

    while(iss.good()){
      double value;
      iss >> value;
      val_feature[index++] = value;
    }
    int *val_bin = new int[feature_dim];
    hamming.calBinaryFeature(val_feature, val_bin);
    val_data.push_back(val_bin);

    delete [] val_feature; 
  }

  val_file.close();
  train_file.close();

  auto cmp = [](pair<int, int> const &a, pair<int, int> const &b)
  {
    return a.second < b.second;
  };

  ofstream ofile;
  ofile.open("/home/xt/tong/mopsi/feature/keras/files/result/diff/ham_1.txt");
 
  for(int i = 0; i < val_data.size(); i++){
    clock_t t = clock();
    vector<int> result = hamming.searchInTable(val_data[i]);
    vector<pair<int,int>> hamming_result;

    for(int m = 0; m < result.size(); m++) {
      int hamming_dis = hamming.calHammingDistance(val_data[i], train_data[result[m]], feature_dim);
      hamming_result.push_back(make_pair(result[m], hamming_dis));
    }

    sort(hamming_result.begin(), hamming_result.end(), cmp);

    ofile << float(clock() - t) / CLOCKS_PER_SEC << ",";
    for(int m = 0; m < 30; m++)
      ofile << hamming_result[m].first << ":"  << hamming_result[m].second << ",";

    ofile << endl;
  } 

  ofile.close();

  return 0; 
}

