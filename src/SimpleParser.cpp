#include "SimpleParser.h"

int SimpleParser::from_phylip_file(const char *file_path) {
    
    ifstream fin;
    fin.open(file_path, ios_base::in);
    fin>>n;
    rows = n-1;
    offset.resize(2*n);
    offsetD.resize(n);
    taxa.resize(2*n, false);
    for(size_t i = 0; i < n; i++) {
        offset[i] = i;
        offsetD[i] = i;
        taxa[i] = true;
    }
    unused.resize(2*n, false);
    leafLabels.resize(n);
    D.resize(n, vector<double>(n));
    size_t i,j;
    for(i=0;i<n;i++){
        fin>>leafLabels[i];
        for(j=0;j<n;j++){
            fin>>D[i][j];
        }
    }
    
    fin.close();
    
    // EXIT_FAILURE if anything goes wrong
    return EXIT_SUCCESS;
}

void SimpleParser::dfs(size_t curNode, bool isLast){

    bool isLeaf = false;
    if(curNode < leafLabels.size())
        isLeaf = true;
    visited[curNode] = true;
    if(!isLeaf)
        fout<<'(';
    else {
        if(!isLast)
            fout << leafLabels[curNode] << ",";
        else
            fout << leafLabels[curNode];
    }

    size_t sz = (*T)[curNode].size();
    for(size_t i=0; i<sz; i++){
        size_t neighbor = (*T)[curNode][i].neighbor;
        if(!visited[neighbor]){
            if(numNeighborsLeft[curNode] == 1)
                dfs(neighbor, true);
            else
                dfs(neighbor, false);
            numNeighborsLeft[curNode] -= 1;
        }
    }

    if(!isLeaf)
      fout<<")";
}

int SimpleParser::to_newick_file(vector<vector<Edge>>* T, const char *file_path) {
    // EXIT_FAILURE if anything goes wrong

    this->T = T;

    fout.open(file_path, ios_base::out);
    visited.resize(T->size(), false);
    numNeighborsLeft.resize(T->size(),0);
    for(size_t i = 0; i<T->size();i++){
        numNeighborsLeft[i] = (*T)[i].size();
    }
    fout<<'(';
    dfs(0,false);
    fout<<')'<<endl;
    fout.close();

    return EXIT_SUCCESS;
}
