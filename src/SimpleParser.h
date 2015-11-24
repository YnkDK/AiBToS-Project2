#ifndef AIBTOS_PROJECT2_SIMPLEPARSER_H
#define AIBTOS_PROJECT2_SIMPLEPARSER_H

#include <stdlib.h>
#include "interface/Parser.h"

class SimpleParser : public Parser {
private:
    vector<vector<double>> D;
    vector<size_t> offset;
    vector<bool> unused;
    size_t last_delete;
    size_t rows;


public:
    /**
     * Get the distance between i and j
     */
    inline double get_d(const size_t i, const size_t j) {
        return D[offset[i]][offset[j]];
    }

    /**
     * Sets the distance between i and j
     */
    inline void set_d(const size_t i, const size_t j, const double value) {
        D[offset[i]][offset[j]] = value;
    }
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
        unused[last_delete] = false;
        return rows;
    }
    /**
     * Returns true if row/column is not used anymore, false otherwise
     */
    inline bool unused_d(const size_t i) {
        return unused[offset[i]];
    }

    int from_phylip_file(const char *file_path);
    int to_newick_file(vector<vector<Edge>>& T, const char *file_path);

};


#endif //AIBTOS_PROJECT2_SIMPLEPARSER_H
