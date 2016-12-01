#include <iostream>
#include <sstream>
#include <random>
#include <unordered_map>
#include <math.h>
#include <vector>
#include <string>
#include <functional>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

const int dim_feature = 65536;  // dimention of feature
const int max_rgb = 255;         // max value of each dimention
const int max_birgb = log(max_rgb + 1)/log(2);  // max binary length of max_rgb
const int num_hash = 2;         // number of hash values
const int num_bit = 30;          // length of hash values
const int dim_bit_feature = dim_feature * max_rgb; // length of bit-value feature
int hash_vector[num_hash][num_bit];       // random index of hash functions

unordered_map<size_t , vector<int>> lsh_map;

void getHashVector();
void getBinaryFeature(int* feature, int* bin_feature);
size_t generateHashKey(int* feature, int hash_index);
void generateHashMap(int* feature, int index);
vector<int> search_index(int* data);

int main()
{
  getHashVector();
  Mat image;
  image = imread("a.JPEG", 0);
  int img[dim_feature] = {0};

  for(int i = 0; i < image.rows; i++){
    for(int j = 0; j < image.cols; j++){
      img[i*256 + j] = image.ptr<uchar>(i)[j];
    }
  }
  
  generateHashMap(img, 50);
/*
  int *bin_img = new int[dim_bit_feature];
  getBinaryFeature(img, bin_img);

  size_t temp_key;

  for(int m = 0; m < num_hash; m++){
    temp_key = generateHashKey(bin_img, m);
    cout << m << "  " << temp_key << endl;
    cout << lsh_map[temp_key][0] << endl;
  }

  */

  vector<int> result = search_index(img);

  for(int it = 0; it < result.size(); it++){
    cout << result[it] << "   ";
  }
  
  //cout << img_hash_key << endl;
  //for(int m = 0; m < dim_bit_feature; m++) cout << bin_img[m] << " ";
  
  //delete[] bin_img;

  imshow("Display window", image);
  // for(int i = 0; i < 30; i++) cout << hash_vector[0][i] << "   " << hash_vector[1][i] << endl;
  waitKey(0);
  return 0;
}


void getHashVector()
{
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> rd_int(0, dim_bit_feature);
  
  for(int m = 0; m < num_hash; m++){
    for(int n = 0; n < num_bit; n++){
      hash_vector[m][n] = rd_int(gen);
    }
  }
}


void getBinaryFeature(int* feature, int* bin_feature){
  for(int i = 0; i < dim_feature; i++){
    for(int j = 0; j < feature[i]; j++){
      bin_feature[i * max_rgb + j] = 1;
    }
  }
}

size_t generateHashKey(int* bin_feature, int hash_index)
{
  stringstream ostr;
  for(int i = 0; i < num_bit; i++) {
    ostr << bin_feature[hash_vector[hash_index][i]]; 
  }

  string str1 = ostr.str();
  hash<string> str_hash;  
  return str_hash(str1);
}


void generateHashMap(int* feature, int index)
{
  int *bin_feature = new int[dim_bit_feature] ();
  getBinaryFeature(feature, bin_feature);
  for(int i = 0; i < num_hash; i++){
    size_t hash_key = generateHashKey(bin_feature, i);
    auto it = find(lsh_map[hash_key].begin(), lsh_map[hash_key].end(), index);
    if(it == lsh_map[hash_key].end()){
      lsh_map[hash_key].push_back(index);
    }
  }
}


vector<int> search_index(int* data)
{
  vector<int> index_list;
  int *bin_feature = new int[dim_bit_feature] ();
  getBinaryFeature(data, bin_feature);

  for(int i = 0; i < num_hash; i++){
    size_t hash_key = generateHashKey(bin_feature, i);
    for(auto it = lsh_map[hash_key].begin(); it != lsh_map[hash_key].end(); it++){
      index_list.push_back(*it);
    }   
  }

  sort(index_list.begin(), index_list.end());
  index_list.erase(unique(index_list.begin(), index_list.end()), index_list.end());

  return index_list;
}

