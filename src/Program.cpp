#include <stdlib.h>
#include <iostream>

#include "SimpleParser.h"
#include "Naive.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        std::cerr << "Usage: ./Program input_path output_path" << std::endl;
        return EXIT_FAILURE;
    }
    int exit_status;
    SimpleParser parser;
    Naive nj;

    exit_status = parser.from_phylip_file(argv[1]);
    if(exit_status != EXIT_SUCCESS) return exit_status;
    exit_status = nj.run(parser);
    if(exit_status != EXIT_SUCCESS) return exit_status;
    exit_status = parser.to_newick_file(nj.getT(), argv[2]);
    return exit_status;
}