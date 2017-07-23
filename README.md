# Locality Sensitive Hashing (LSH) and Dynamic Continuous Indexing (DCI)

The generalization of cameras and the increase of storage capacities make data analysis more and more important. Given an image, we need an efficient algorithm to search similar images in a huge dataset. The principle idea of this project is to do quick research in a huge image dataset with help of convolutional neural network(CNN) descriptor. To solve this problem, K-nearest neighbour algorithm (KNN) is widely used. In this project, LSH and DCI are implemented and tested.

## Requirement

* Python 2.7, Scipy, Numpy
* Keras
* g++ (the version should support c++ 11)

## Function

* Calculate image discriptors by convolutional neural network (Python + Keras)
* Implement LSH based on different distances (Cosine distance, Jaccard distance, Hamming distance, Euclidean distance) (C++)
* Implement DCI (C++)

## Run

`sh run.sh`



