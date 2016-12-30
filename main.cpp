#include "lshhamming.h"
#include "lshcosine.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

const int feature_dim = 4096;
const int num_hash_vec = 7;

int main()
{
  //LSH_Hamming Hamming(65536, 255, 2, 30);
  LSH_Cosine cosine(feature_dim, num_hash_vec);
  vector<double*> train_data;
  vector<double*> val_data;
  
  //ifstream file("/home/xt/tong/mopsi/feature/imagenet_20_feature.txt");
  ifstream val_file("/home/xt/tong/mopsi/feature/test.txt");
  ifstream train_file("/home/xt/tong/mopsi/feature/val_feature.txt");
  string line;
  int num_feature = 0;

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
    num_feature++;
  }

  cout << "The number of features: " << num_feature << endl;

  for(int n = 0; n < num_feature; n++){
    int *bin_feature = new int[num_hash_vec];
    cosine.calBinaryFeature(train_data[n], bin_feature);
    cosine.updateHashMap(bin_feature, n);
  }  

  /*-----------------val-------------------*/
  double *val_feature = new double[feature_dim];

  while(val_file.good()){
    int index = 0;

    getline(val_file, line);
    if(line.length() < feature_dim) break;
    istringstream iss(line);

    while(iss.good()){
      double value;
      iss >> value;
      val_feature[index++] = value;
    }
    cout << index << endl;
  }

  int* val_bin = new int[num_hash_vec];
  cosine.calBinaryFeature(val_feature, val_bin);
  vector<int> result = cosine.searchInTable(val_bin);  
  vector<pair<int,double>> cos_result;

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
    cout << cos_result[m].first << "   "  << cos_result[m].second << endl;   
/*
  for(int m = 0; m < train_data.size(); m++) {
    double cos_dis = cosine.cosine_similarity(val_feature, train_data[m], feature_dim);
    cos_result.push_back(make_pair(m, cos_dis));
  }

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {  
    return a.second > b.second;
  };

  sort(cos_result.begin(), cos_result.end(), cmp);

  for(int m = 0; m < 20; m++)
    cout << cos_result[m].first << "    " << cos_result[m].second << endl;
*/ 
  return 0; 
}

