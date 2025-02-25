#include "TriangleParser.h"

int TriangleParser::from_phylip_file(const char *file_path) {
    
    ifstream fin;
    fin.open(file_path, ios_base::in);
    fin>>n;
    rows = n-1;
    offset.resize(2*n);
    offsetD.resize(n);
    for(size_t i = 0; i < n; i++) {
        offset[i] = i;
        offsetD[i] = i;
    }
    unused.resize(2*n, false);
    leafLabels.resize(n);
    D.resize(n);
    size_t i,j;
    double upper;
    for(i=0;i<n;i++){
        D[i].resize(i+1);
        fin>>leafLabels[i];
        for(j=0;j<n;j++){
            if(j<i+1) fin >> D[i][j];
            else fin >> upper;
        }
    }
    
    fin.close();
    
    // EXIT_FAILURE if anything goes wrong
    return EXIT_SUCCESS;
}

void TriangleParser::dfs(size_t curNode, double weight){

    //we just visited the curNode, so mark it
    visited[curNode] = true;
    //if the curNode is not a leaf we have to print a left parenthesis
    if(!isLeaf(curNode)) {
        cout << '(';
    }
    //sz will save the number of neighbours of curNode
    size_t sz = (*T)[curNode].size();
    //for every neighbor of curNode
    for(size_t i=0; i<sz; i++){
        //pick the next neighbor
        size_t neighbor = (*T)[curNode][i].neighbor;
        //if we visited it then do nothing
        if(!visited[neighbor]){
            //otherwise visit the neighbor
            dfs(neighbor, (*T)[curNode][i].weight);
            //now we need to know what character to print next. If there are more nodes remained to visit, then we print a comma. Otherwise we print nothing and will later (after for loop) print a right parenthesis.
            size_t numNodesLeft = 0;
            for(size_t j = i+1; j < sz; j++){
                size_t neighbor2 = (*T)[curNode][j].neighbor;
                if(!visited[neighbor2]){
                    numNodesLeft++;
                }
            }
            if(numNodesLeft>0)
                cout<<',';
        }
    }
    //if the current node is the starting node then we print );
    if(curNode == (*T)[0][0].neighbor) {
        cout << ");";
    }
        //else if it's an internal node we print ): and the weight
    else if(!isLeaf(curNode)){
        cout<<"):"<<weight;
    }
        //else if it's neither an internal node nor the starting node, it must be a leaf so print the name of the leaf together with the weight
    else{
        cout << leafLabels[curNode] <<":"<< weight;
    }
}

int TriangleParser::to_newick_file(vector<vector<Edge>>* T) {
    // EXIT_FAILURE if anything goes wrong
    this->T = T;
    visited.resize(T->size(), false);
    dfs((*T)[0][0].neighbor, (*T)[0][0].weight);
    return EXIT_SUCCESS;
}
