
//
#ifndef AIBTOS_PROJECT2_PARSER_H
#define AIBTOS_PROJECT2_PARSER_H



class Parser {
public:
    virtual int from_phylip_file(const char *file_path) = 0;
    virtual int to_newick_file(const char *file_path) = 0;
};

#endif //AIBTOS_PROJECT2_PARSER_H
