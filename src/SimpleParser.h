#ifndef AIBTOS_PROJECT2_SIMPLEPARSER_H
#define AIBTOS_PROJECT2_SIMPLEPARSER_H

#include <stdlib.h>
#include "interface/Parser.h"
#include <fstream>

class SimpleParser {
private:
    vector<size_t> offsetD;
    size_t last_delete;
    vector<vector<Parser::Edge>> *T;
    void dfs(size_t curNode, double weight);
    vector<bool> visited;


    vector<size_t> numNeighborsLeft;
    inline bool isLeaf(size_t node){
        return node < leafLabels.size();
    }
public:
    vector<vector<double>> D;
    vector<bool> unused;
    vector<size_t> offset;
    size_t rows;
    vector<string> leafLabels;
    size_t n;

    /**
     * Removes the row i and column i in d
     */
    inline void delete_d(const size_t i) {
        last_delete = offset[i];
        unused[offset[i]] = true;
    }

    /**
     * Adds a new row and column in d and returns the new node id
     */
    inline size_t add_node() {
        rows++;
        offset[rows] = last_delete;
        if(last_delete < n){
            offsetD[last_delete] = rows;
        }
        unused[last_delete] = false;
        return rows;
    }

    
    inline size_t getNextId(){
        return rows+1;
    }
    inline size_t getOffset(size_t i){
        return offset[i];
    }

    inline size_t getOffsetD(size_t i){
        return offsetD[i];
    }

    inline void printD(){
        
        for(size_t i=0;i<D.size();i++){
            for(size_t j=0;j<D[i].size();j++){
                cout<<D[i][j]<<" ";
            }
            cout<<endl;
        }
        
    }
    
    inline void printOffset(){
        
        for(size_t i=0; i<offset.size();i++){
            cout<<offset[i]<<" ";
        }
        cout<<endl;
    
    }

    int from_phylip_file(const char *file_path);
    int to_newick_file(vector<vector<Parser::Edge>>* T);

};


#endif //AIBTOS_PROJECT2_SIMPLEPARSER_H
