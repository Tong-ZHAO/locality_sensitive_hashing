#include "lshdci.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

/* set parameters*/
// feature dimension
const int feature_dim = 4096;
// length of simple imdex
const int len_vector = 20;
// number of simple index
const int num_vector = 3;
// maximum number of candidate points
const int max_number = 50; 

int main()
{
  /* build model */
  LSH_Dci dci(feature_dim, len_vector, num_vector, max_number);

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

  train_file.close();
  cout << "The number of features: " << train_data.size() << endl;

  /* set search tables*/ 
  for(int n = 0; n < train_data.size(); n++)
    dci.updateHashMap(train_data[n], n);

  /* load val data*/
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

  ofstream ofile;
  ofile.open("/home/xt/tong/mopsi/feature/keras/files/result/diff/dci_1.txt");

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {
    return a.second < b.second;
  };

  for(int i = 0; i < val_data.size(); i++){
    clock_t t = clock();
    vector<int> result = dci.searchInTable(val_data[i]);
    vector<pair<int, double>> dci_result;

    for(int m = 0; m < result.size(); m++) {
      double dci_dis = dci.calEuclideanDistance(val_data[i], train_data[result[m]], feature_dim);
      dci_result.push_back(make_pair(result[m], dci_dis));
    }


    sort(dci_result.begin(), dci_result.end(), cmp);

    ofile << float(clock() - t) / CLOCKS_PER_SEC << ",";
    for(int m = 0; m < dci_result.size(); m++)
      ofile << dci_result[m].first << ":"  << dci_result[m].second << ","; 

    ofile << endl;
  }
  /*----------------compare all-----------------

  vector<pair<int, double>> euc_result;

  for(int m = 0; m < train_data.size(); m++) {
    double euc_dis = dci.calEuclideanDistance(val_feature, train_data[m], feature_dim);
    euc_result.push_back(make_pair(m, euc_dis));
  }

  auto cmp = [](pair<int, double> const &a, pair<int, double> const &b)
  {  
    return a.second < b.second;
  };

  sort(euc_result.begin(), euc_result.end(), cmp);

  for(int m = 0; m < 50; m++)
    cout << euc_result[m].first << "    " << euc_result[m].second << endl;
*/
  return 0; 
}

