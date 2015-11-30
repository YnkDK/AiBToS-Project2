#!/usr/bin/env bash

# Setup the binary for this project
mkdir -p tmp/
cd tmp/
cmake ..
make
mv bin/AiBToS_Project2 ../bin/
cd ..

# Run all phy-files with our program, QuickTree and RapidNJ
for f in unique_distance_matrices/*.phy; do
    # Extract instance from filename
    instance=${f}
    instance=${instance#unique_distance_matrices/}
    instance=${instance%.phy}
    # Time our implementation
    START=$(date +%s%3N)
    ./bin/AiBToS_Project2 ${f} >/dev/null
    END=$(date +%s%3N)
    echo "AiBToS_Project2 ${instance} $((END-START))"
    # Time QuickTree
    START=$(date +%s%3N)
    ./bin/quicktree -in m ${f} >/dev/null
    END=$(date +%s%3N)
    echo "QuickTree ${instance} $((END-START))"
    # Time RapidNJ
    START=$(date +%s%3N)
    ./bin/rapidnj -i pd ${f} >/dev/null
    END=$(date +%s%3N)
    echo "RapidNJ ${instance} $((END-START))"
done