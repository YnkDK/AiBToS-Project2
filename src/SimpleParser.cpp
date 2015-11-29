#include "SimpleParser.h"

int SimpleParser::from_phylip_file(const char *file_path) {
    
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

void SimpleParser::dfs(size_t curNode, double weight){

    //we just visited the curNode, so mark it
    visited[curNode] = true;
    //if the curNode is not a leaf we have to print a left parenthesis
    if(!isLeaf(curNode)) {
        fout << '(';
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
                    fout<<',';
        }
    }
    //if the current node is the starting node then we print );
    if(curNode == (*T)[0][0].neighbor) {
        fout << ");";
    }
    //else if it's an internal node we print ): and the weight
    else if(!isLeaf(curNode)){
        fout<<"):"<<weight;
    }
    //else if it's neither an internal node nor the starting node, it must be a leaf so print the name of the leaf together with the weight
    else{
        fout << leafLabels[curNode] <<":"<<(*T)[curNode][0].weight;
    }
}

int SimpleParser::to_newick_file(vector<vector<Edge>>* T, const char *file_path) {
    // EXIT_FAILURE if anything goes wrong

    this->T = T;

    fout.open(file_path, ios_base::out);
    visited.resize(T->size(), false);
    dfs((*T)[0][0].neighbor, (*T)[0][0].weight);
    fout.close();

    return EXIT_SUCCESS;
}
