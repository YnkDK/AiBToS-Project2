
//
#ifndef AIBTOS_PROJECT2_PARSER_H
#define AIBTOS_PROJECT2_PARSER_H

#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Parser {
public:
    
    struct Edge{
        size_t neighbor;
        double weight;
    };
    size_t n;
    vector<string> leafLabels;
    
    virtual int from_phylip_file(const char *file_path) = 0;
    virtual int to_newick_file(vector<vector<Edge>>& T, const char *file_path) = 0;
};

#endif //AIBTOS_PROJECT2_PARSER_H
