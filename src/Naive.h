#ifndef AIBTOS_PROJECT2_NAIVE_H
#define AIBTOS_PROJECT2_NAIVE_H


#include "interface/NeighborJoining.h"

class Naive : public NeighborJoining {

private:
    vector<vector<Parser::Edge>> T;

public:
    int run(Parser &parser);
    vector<vector<Parser::Edge>> * getT(){
        return &T;
    }

};


#endif //AIBTOS_PROJECT2_NAIVE_H
