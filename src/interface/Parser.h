
//
#ifndef AIBTOS_PROJECT2_PARSER_H
#define AIBTOS_PROJECT2_PARSER_H

#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <iostream>

using namespace std;

class Parser {
public:
    
    struct Edge{
        size_t neighbor;
        double weight;
    };
    size_t n;
    vector<string> leafLabels;

    virtual double get_d(const size_t i, const size_t j) = 0;
    virtual void set_d(const size_t i, const size_t j, const double value) = 0;
    virtual void delete_d(const size_t i) = 0;
    virtual size_t add_node() = 0;
    virtual bool unused_d(const size_t i) = 0;
    virtual int from_phylip_file(const char *file_path) = 0;
    virtual int to_newick_file(vector<vector<Edge>>* T) = 0;
    virtual void printD() = 0;
    virtual size_t getNextId() = 0;
    virtual void printOffset() = 0;
    virtual size_t getOffset(size_t i) = 0;
    virtual size_t getOffsetD(size_t i) = 0;
};

#endif //AIBTOS_PROJECT2_PARSER_H
