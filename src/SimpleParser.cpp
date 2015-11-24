#include "SimpleParser.h"

int SimpleParser::from_phylip_file(const char *file_path) {
    
    ifstream fin;
    fin.open(file_path, ios_base::in);
    
    fin>>n;
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

int SimpleParser::to_newick_file(vector<vector<Edge>>& T, const char *file_path) {
    // EXIT_FAILURE if anything goes wrong
    return EXIT_SUCCESS;
}
