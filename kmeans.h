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

//The constructor initializes some variables
KMeans::KMeans(int n_clusters, int data_size_in)
{
    num_clusters = n_clusters;
    data_size = data_size_in;
    vector<vector<float>> R (data_size, vector<float>(num_clusters));
    static vector<vector<int>> indices (num_clusters, vector<int> (data_size, -1));
    this->indices = indices;
};

//To find the initial centroids, "random" points are taken from the dataset
void KMeans::def_initial_centroids(vector<float> data_in, int data_size_in, int n_clusters, char method)
{
    srand(time(0));
    //TODO: Implement a check for data_size_in and n_clusters
    vector<float>::iterator it;
    data = data_in;
    data_size = data_size_in;
    num_clusters = n_clusters;
    int index[num_clusters];

    //First we initialize an array with n_clusters
    for (int j=0;j<data_size;j++)
    {
        index[j] = j;
    }
    //now we shuffle it to get "random" centroids
    shuffle(index,data_size);
    // and we assign an initial value to the cluster
    vector<int> temp;
    for (int i=0;i<num_clusters;i++)
    {
        it = data_in.begin() + index[i];
        temp.push_back(index[i]);
        centroids.push_back(*it);
    }
    // indices.insert(indices.begin(),temp);
}

//The clustering function will assign everypoint of the dataset to a cluster and recalculate the centroid as the mean of everypoint on it

void KMeans::clustering(vector<float> data_in)
{
    vector<vector<float>> R (data_size, vector<float>(num_clusters));
    vector<float> ctemp;
    vector<float> sub_vector;
    vector<float>::iterator it_d;
    vector<float>::iterator it_c;
    ctemp = centroids;
    vector<vector<float>> dists(data_size, vector<float> (num_clusters, 0));
    int min_ind;
    float min_dis;


    R.insert(R.begin(), ctemp);

    //Calculate all distances between the centroids and the data points
    int n =0, i=0;
    for (it_d = data_in.begin();it_d<data_in.end();it_d++)
    {
        i=0;
        for(it_c = centroids.begin();it_c<centroids.end();it_c++)
        {
            dists[n][i] = distance(*it_d,*it_c);
            i++;
        }
        //Find the closest centroid and assign the data point to it
        sub_vector.reserve(num_clusters);
        sub_vector = dists[n];
        vector<float>::iterator result = min_element(sub_vector.begin(), sub_vector.end());
        min_ind = std::distance(sub_vector.begin(), result);
        min_dis = *result;
        R[n+1][min_ind]=data_in[n];
        indices[min_ind][n] = n;
        recalculate_centroid(min_ind,n,R);

         n++;
    }
    //clear the '-1' from the vector
    vector<int>::iterator ind;
    for(int i = 0;i<num_clusters;i++)
    {
        do{
        ind = find(indices[i].begin(), indices[i].end(), -1);
        if(ind != indices[i].end() ) indices[i].erase(ind);
        }while(ind != indices[i].end() );
    }

}

//This function will print the centroids
void KMeans::print_centroids()
{
    vector<float>::iterator it;
    cout<<"There are " << num_clusters << " centroids :"<<endl;
    for (it = centroids.begin(); it != centroids.end(); ++it)
    cout<<*it<<" ";

    cout<<endl;
}

//This function is auxiliary to define the initial centroids
void KMeans::shuffle(int *arr, size_t n)
{
    if (n > 1)
    {
        size_t i;
        srand(time(NULL));
        for (i = 0; i < n - 1; i++)
        {
          size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
          int t = arr[j];
          arr[j] = arr[i];
          arr[i] = t;
        }
    }
}

//function to calculate the distance betweem two points
float KMeans::distance(float in1, float in2)
{
    return abs(abs(in1)-abs(in2));

}

//function to update the centroid based
void KMeans::recalculate_centroid(int c_index, int d_index,vector<vector<float>> vIn)
{
    int count=0;
    float res=0;
    for(int i=0;i<(d_index+2);i++)
    {
        if(vIn[i][c_index]>0)
        {
            count ++;
            res += vIn[i][c_index];
        }

    }
    res = res/count;
    centroids[c_index] =res;
}

//function to print the members of a cluster
void KMeans::print_members(int ind_centroid)
{
    // cout<<indices[0][0]<<endl;
    // cout<<indices[0][1]<<endl;
    vector<int>::iterator it;
    cout<<"These are the members of cluster: " << ind_centroid <<endl;
    for (it = this->indices[ind_centroid].begin(); it != this->indices[ind_centroid].end(); ++it) cout<<data[*it]<<" ";
    cout<<endl;

}

//function that return the members of a cluster
vector<float> KMeans::get_members(int ind_centroid)
{
    vector<float> sub;
    vector<int>::iterator it;
    for (it = this->indices[ind_centroid].begin(); it != this->indices[ind_centroid].end(); ++it)
     sub.push_back(data[*it]);

    return sub;
}

//function that returns the indices of the cluster members.
//Note that the indices are related to the original dataset
vector<int> KMeans::get_index_members(int ind_centroid)
{
    vector<int> sub;
    vector<int>::iterator it;
    for (it = this->indices[ind_centroid].begin(); it != this->indices[ind_centroid].end(); ++it)
     sub.push_back(*it);

    return sub;
}


#endif // KMEANS_H
