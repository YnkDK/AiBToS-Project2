import numpy
from Bio import Phylo
from sys import argv


def to_adjacency_matrix(tree):
    """Create an adjacency matrix (NumPy array) from clades/branches in tree.
 
    Also returns a list of all clades in tree ("all_clades"), where the position
    of each clade in the list corresponds to a row and column of the numpy
    array: a cell (i,j) in the array is 1 if there is a branch from all_clades[i]
    to all_clades[j], otherwise 0.
 
    Returns a tuple of (all_clades, adjacency_matrix) where all_clades is a list
    of clades and adjacency_matrix is a NumPy 2D array.

    Source: http://biopython.org/wiki/Phylo_cookbook#Convert_to_a_NumPy_array_or_matrix
    """
    all_clades = list(tree.find_clades(order='level'))
    lookup = {}
    for i, elem in enumerate(all_clades):
        lookup[elem] = i
    adjacency_matrix = numpy.zeros((len(all_clades), len(all_clades)))
    for parent in tree.find_clades(terminal=False, order='level'):
        for child in parent.clades:
            adjacency_matrix[lookup[parent], lookup[child]] = 1
    if not tree.rooted:
        # Branches can go from "child" to "parent" in unrooted trees
        adjacency_matrix += adjacency_matrix.transpose()  # Fixed an error here
    return all_clades, adjacency_matrix

clades, adjacent = to_adjacency_matrix(Phylo.read(argv[1], 'newick'))

leaves = dict()
internal = dict()
mapping = dict()
adjacency_list = dict()

for idx, row in enumerate(adjacent):
    if 0.5 < sum(row) < 1.5:
        leaves[clades[idx].name] = idx

i = 0
for name in sorted(leaves.keys()):
    mapping[leaves[name]] = i
    i += 1

for idx, row in enumerate(adjacent):
    if sum(row) > 1.0:
        mapping[idx] = i
        i += 1

for idx, row in enumerate(adjacent):
    tmp = list()
    for neighbor, element in enumerate(row):
        if element > 0.5:
            tmp.append(mapping[neighbor])
    adjacency_list[mapping[idx]] = tmp

with open(argv[1][:-7] + '.adj', 'wb') as f:
    f.write(bytes(str(len(adjacency_list)), 'utf8') + b"\n")
    for k in sorted(adjacency_list.keys()):
        f.write(bytes(str(len(adjacency_list[k])), 'utf8') + b' ')
        f.write(bytes(' '.join(map(str, adjacency_list[k])), 'utf8'))
        f.write(b'\n')
