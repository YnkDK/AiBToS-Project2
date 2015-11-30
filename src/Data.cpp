#include "Data.h"

int Data::from_phylip_file(const char *file_path) {
    ifstream fin;
    fin.open(file_path, ios_base::in);
    if(!fin.is_open()) {
        cerr << "Could not open file " << file_path << endl;
        return EXIT_FAILURE;
    }
    fin>>n;

    leafLabels.resize(n);
    D = new double*[n];

    size_t i,j;
    double upper_value;
    for(i=0;i<n;i++){
        fin>>leafLabels[i];
        D[i] = new double[i+1];
        for(j=0;j<n;j++){
            if(j <= i) {
                fin>>D[i][j];
            } else {
                fin>>upper_value;
            }
        }
    }

    fin.close();
    return EXIT_SUCCESS;
}

void Data::dfs(const size_t curNode, const double weight) {

    //we just visited the curNode, so mark it
    visited[curNode] = true;
    //if the curNode is not a leaf we have to print a left parenthesis
    if(IS_INTERNAL(curNode)) {
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
    else if(IS_INTERNAL(curNode)){
        cout<<"):"<<weight;
    }
        //else if it's neither an internal node nor the starting node, it must be a leaf so print the name of the leaf together with the weight
    else{
        cout << leafLabels[curNode] <<":"<< weight;
    }
}

int Data::to_newick_file(vector<vector<Edge>>* T) {
    // EXIT_FAILURE if anything goes wrong

    this->T = T;
    visited.resize(T->size(), false);
    dfs((*T)[0][0].neighbor, (*T)[0][0].weight);
    return EXIT_SUCCESS;
}

