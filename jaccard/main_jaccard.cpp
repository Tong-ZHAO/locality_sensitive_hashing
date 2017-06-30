#include "lshjaccard.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>

using namespace std;

const int feature_dim = 4096;
const int num_hash_vec = 16;
const int num_per_hash = 5;

int main()
{
  LSH_Jaccard jaccard(feature_dim, num_hash_vec, num_per_hash);
  vector<double*> train_data;
  vector<double*> val_data;
  
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
    train_data.push_back(feature);
  }

  cout << "The number of features: " << train_data.size() << endl;
 
  vector<int*> train_bin;

  for(int n = 0; n < train_data.size(); n++){
    int *bin_feature = new int[feature_dim];
    jaccard.calBinaryFeature(train_data[n], bin_feature);
    jaccard.updateHashMap(bin_feature, n);
    train_bin.push_back(bin_feature);
  }

  /*-----------------val-------------------*/

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
    val_data.push_back(val_feature);
  }

  val_file.close();
  train_file.close();

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {
    return a.second < b.second;
  };

  ofstream ofile;
  ofile.open("/home/xt/tong/mopsi/feature/keras/files/result/diff/jac_1.txt");

  for(int i = 0; i < val_data.size(); i++){
    time_t t = clock();
    int* val_bin = new int[feature_dim];
    jaccard.calBinaryFeature(val_data[i], val_bin);
    vector<int> result = jaccard.searchInTable(val_bin);

    
    vector<pair<int, double>> jaccard_result;

    for(int m = 0; m < result.size(); m++) {
      double jaccard_dis = jaccard.calJaccardDistance(val_bin, train_bin[result[m]], feature_dim);
      jaccard_result.push_back(make_pair(result[m], jaccard_dis));
    }

    sort(jaccard_result.begin(), jaccard_result.end(), cmp);

    ofile << float(clock() - t) / CLOCKS_PER_SEC << ";"; 
    for(int m = 0; m < jaccard_result.size(); m++)
      ofile << jaccard_result[m].first << ":"  << jaccard_result[m].second << ",";

    ofile << endl;
  }

  ofile.close(); 


/* 
  val_bin = new int[num_hash_vec];
  cosine.calBinaryFeature(val_feature, val_bin);
  vector<int> result = cosine.searchInTable(val_bin);  */
/*
  vector<pair<int, double>> jaccard_result;

  for(int m = 0; m < result.size(); m++) {
    double cos_dis = cosine.cosine_similarity(val_feature, train_data[result[m]], feature_dim);
    if(cos_dis > 0.15)  cos_result.push_back(make_pair(result[m], cos_dis));
  }

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {  
    return a.second > b.second;
  };

  sort(cos_result.begin(), cos_result.end(), cmp);

  for(int m = 0; m < cos_result.size(); m++)
    cout << cos_result[m].first << "   "  << cos_result[m].second << endl;   */

  /*----------------compare all-----------------

  vector<pair<int, double>> jac_result;

  for(int m = 0; m < train_data.size(); m++) {
    double jac_dis = jaccard.calJaccardDistance(val_bin, train_bin[m], feature_dim);
    cout << jac_dis << endl;
    jac_result.push_back(make_pair(m, jac_dis));
  }

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {  
    return a.second < b.second;
  };

  sort(jac_result.begin(), jac_result.end(), cmp);

  for(int m = 0; m < 50; m++)
    cout << jac_result[m].first << "    " << jac_result[m].second << endl;
 */

  return 0; 
}

