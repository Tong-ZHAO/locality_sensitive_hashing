#include "lshcosine.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cmath>
#include <time.h>

using namespace std;

/* set parameters*/
// feature dimension
const int feature_dim = 4096;
// length of hash vector (size of hash map)
const int num_hash_vec = 6;
// number of hash map
const int num_hash_map = 8;


int main()
{
  /* build model */
  LSH_Cosine cosine(feature_dim, num_hash_vec, num_hash_map);

  /* open data file */
  vector<double*> train_data;
  vector<double*> val_data;
  
  ifstream val_file("/home/xt/tong/mopsi/feature/keras/files/t20000_val_feature.txt");
  ifstream train_file("/home/xt/tong/mopsi/feature/keras/files/t20000_feature.txt");
  string line;

  /* load train data */
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

  /* set up hash map */
  for(int n = 0; n < train_data.size(); n++)
    cosine.updateHashMap(train_data[n], n);

  /* load val data */
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
    return a.second > b.second;
  };

  ofstream ofile;               
  ofile.open("/home/xt/tong/mopsi/feature/keras/files/result/diff/cos_res.txt");

  /* validation */
  for(int i = 0; i < val_data.size(); i++){
    // calculate execute time
    clock_t t = clock();
    vector<int> result = cosine.searchInTable(val_data[i]);
    vector<pair<int,double>> cos_result;

    // find k-nearest neighbour
    for(int m = 0; m < result.size(); m++) {
      double cos_dis = cosine.cosine_similarity(val_data[i], train_data[result[m]], feature_dim);
      cos_result.push_back(make_pair(result[m], cos_dis));
    }
    sort(cos_result.begin(), cos_result.end(), cmp);
    
    ofile << float(clock() - t)/CLOCKS_PER_SEC << ',';

    // write result
    for(int m = 0; m < min(30, (int)cos_result.size()); m++)
      ofile << cos_result[m].first << ":"  << cos_result[m].second << ',';

    ofile << endl;
  }

  ofile.close();
  return 0; 
}
