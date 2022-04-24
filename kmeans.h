/****************************************************************
 *  Header File: kmeans.h
 *  Description: kmeans cluster library for 1D float data
 * ---------- ---------- ----------------------------
 *  Tassio BORGES 24-APR-2022  - Created
 *
 * This class implements a kmeans clustering algorithm for 1D float data.
 * The functions can calculate the clusters and return the members of each cluster
 * With a kmeans clustering, one can implement Radial Basis Functions
 ****************************************************************/

#ifndef KMEANS_H
#define KMEANS_H

#include<iostream>
#include<fstream>
#include<vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class KMeans
{
    int num_clusters; //Number of Clusters
    int data_size; //Size of data
    vector<float> centroids; // vector containing the centroids
    vector<float> data; //input dataset to cluster
    vector<vector<float>> R; // 2D Vector containing the centroids and the points assigned to them
    vector<vector<int>> indices;
    void shuffle(int *arr,size_t n); // function to help "randomize" the initial clusters selection
    float distance(float in1, float in2); //calculate the distance between the points
    void recalculate_centroid(int c_index, int d_index,vector<vector<float>> vIn); // Function to recalculate the centroid as the mean of all its points
 public:
    KMeans(int n_clusters, int data_size_in); // Initialize the object with the number of cluster and the data to cluster
    void def_initial_centroids(vector<float> data_in ,int data_size_in, int n_clusters, char method); // "Randomly" select the initial clusters
    void clustering(vector<float> data_in); // Perform the clustering
    void print_centroids(); // print the centroids
    void print_members(int ind_centroid); //print the cluster members
    vector<float> get_members(int ind_centroid); // return the members of a cluster
    vector<int> get_index_members(int ind_centroid); // return the indices of the cluster members, indices are related to the original dataset
};



#endif // KMEANS_H
