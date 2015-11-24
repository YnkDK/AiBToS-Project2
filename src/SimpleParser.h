#ifndef AIBTOS_PROJECT2_SIMPLEPARSER_H
#define AIBTOS_PROJECT2_SIMPLEPARSER_H

#include <stdlib.h>

#include "interface/Parser.h"

class SimpleParser : public Parser {
public:
    int from_phylip_file(const char *file_path);
    int to_newick_file(const char *file_path);
};


#endif //AIBTOS_PROJECT2_SIMPLEPARSER_H
