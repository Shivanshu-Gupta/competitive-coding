cmake_minimum_required(VERSION 3.7)
project(MyLibrary)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        algorithms/DP/fibonacci/fibonacci/fib_n.cpp
#        algorithms/DP/longest_common_subseq/longest_common_subseq/LCS.cpp
#        algorithms/DP/longest_inc_subseq/longest_inc_subseq/lis.cpp
#        algorithms/DP/quine/quine/quine.cpp
#        algorithms/sorting/part_sorting.cpp
        algorithms/bellman-ford.cpp
        algorithms/dijkstra.cpp
        algorithms/FFT.cpp
        algorithms/FFTRecursive.cpp
        algorithms/floyd-warshall.cpp
        algorithms/graph-algorithms.cpp
        algorithms/KMP.cpp
        algorithms/manacher.cpp
        algorithms/max-flow.cpp
        algorithms/min-cost-flow.cpp
        algorithms/modular-exp.cpp
        algorithms/mos-algorithm.cpp
        algorithms/nth-order-statistic.cpp
        algorithms/rabin-karp.cpp
#        algorithms/Search.cpp
        algorithms/sieve-erastosthenes.cpp
        algorithms/sorting-rank.cpp
#        data-structures/SuffixArray1.cpp
        data-structures/suffix-array-2.cpp
        algorithms/z-algorithm.cpp
        data-structures/disjoin-set.cpp
        data-structures/segment-tree-iter.cpp
        data-structures/segment-tree-rec.cpp
#        data-structures/suffixTree.cpp
        data-structures/trie.cpp
#        minLexicRotation.cpp
        util/util.h
        util/util.cpp
        util/matrix.cpp)

add_executable(MyLibrary ${SOURCE_FILES} algorithms/merge-sort.cpp)
add_executable(kth-element algorithms/kth-element.cpp ${SOURCE_FILES})
add_executable(binary-heap data-structures/binary-heap.cpp ${SOURCE_FILES})
add_executable(binary-heap-prio-update data-structures/binary-heap-prio-update.cpp ${SOURCE_FILES})
add_executable(op-overloading c++/op-overloading.cpp)
add_executable(func-templates c++/func-templates.cpp)
add_executable(misc-stl c++/misc-stl.cpp)