#include "lsheuclidean.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

const int feature_dim = 4096;
const int num_hash_vec = 20;
const int num_per_hash = 8;
const int len_bucket = 60;
const int map_size = 5471;

int main()
{
  LSH_Euclidean euclidean(feature_dim, num_hash_vec, num_per_hash, len_bucket, map_size);
  vector<double*> train_data;
  vector<double*> val_data;
  
  //ifstream file("/home/xt/tong/mopsi/feature/imagenet_20_feature.txt");
  ifstream val_file("/home/xt/tong/mopsi/feature/keras/files/test.txt");
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
 
  for(int n = 0; n < train_data.size(); n++)
    euclidean.updateHashMap(train_data[n], n);

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
  ofile.open("/home/xt/tong/mopsi/feature/keras/files/result/euc_1.txt");

  for(int i = 0; i < val_data.size(); i++){
    vector<int> result = euclidean.searchInTable(val_data[i]);
    vector<pair<int, double>> euclidean_result;

    for(int m = 0; m < result.size(); m++) {
      double euclidean_dis = euclidean.calEuclideanDistance(val_data[i], train_data[result[m]], feature_dim);
      euclidean_result.push_back(make_pair(result[m], euclidean_dis));
    }

    sort(euclidean_result.begin(), euclidean_result.end(), cmp);

    for(int m = 0; m < 30; m++)
      ofile << euclidean_result[m].first << "; "  << euclidean_result[m].second << ","; 

    ofile << endl;
  }

  ofile.close();

  /*----------------compare all-----------------

  vector<pair<int, double>> jac_result;

  for(int m = 0; m < train_data.size(); m++) {
    double jac_dis = euclidean.calEuclideanDistance(val_feature, train_data[m], feature_dim);
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

