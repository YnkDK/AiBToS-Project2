#ifndef AIBTOS_PROJECT2_DATASET_H
#define AIBTOS_PROJECT2_DATASET_H


#include <stddef.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <iostream>


#define IS_INTERNAL(i) i >= n

using namespace std;

class Data {
private:
    vector<bool> visited;

    void dfs(const size_t curNode, const double weight);
public:
    struct Edge{
        size_t neighbor;
        double weight;
    };

    vector<string> leafLabels;
    double **D;
    size_t n;
    vector<vector<Edge>> *T;


    int from_phylip_file(const char *file_path);
    int to_newick_file(vector<vector<Edge>>* T);
};


#endif //AIBTOS_PROJECT2_DATASET_H
