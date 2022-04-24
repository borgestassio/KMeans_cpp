//Example to call KMeans algorithm

#include<iostream>
#include<fstream>
#include<vector>
#include "kmeans.h"
using namespace std;




int main()
{
    float test_data[10] = {100.0, 200.0,300.0,400,500,600,700,800,900,10000};
    int num_of_clusters = 5;
    int size_of_data;

    vector<float> data_vector;


    for (int i=0;i<10;i++) data_vector.push_back(test_data[i]);

    size_of_data = data_vector.size();

    vector<float> members;
    vector<int> members_index;

    KMeans kmeans(num_of_clusters,size_of_data);
    kmeans.def_initial_centroids(data_vector ,size_of_data, num_of_clusters, 'r');
    kmeans.print_centroids();
    kmeans.clustering(data_vector);
    cout<<"The new centroids are: "<<endl;
    kmeans.print_centroids();
    kmeans.print_members(1);
    members = kmeans.get_members(1);
    members_index = kmeans.get_index_members(1);

    return 0;
}


