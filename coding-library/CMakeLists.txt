cmake_minimum_required(VERSION 3.7)
project(MyLibrary)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES
#        algorithms/DP/fibonacci/fibonacci/fib_n.cpp
#        algorithms/DP/longest_common_subseq/longest_common_subseq/LCS.cpp
#        algorithms/DP/longest_inc_subseq/longest_inc_subseq/lis.cpp
#        algorithms/DP/quine/quine/quine.cpp
#        algorithms/ordering/part_sorting.cpp
        algorithms/graph/bellman-ford.cpp
        algorithms/graph/dijkstra.cpp
        algorithms/FFT/FFT.cpp
        algorithms/FFT/FFTRecursive.cpp
        algorithms/graph/floyd-warshall.cpp
        algorithms/graph/graph-algorithms.cpp
        algorithms/string/manacher.cpp
        algorithms/graph/max-flow.cpp
        algorithms/graph/min-cost-flow.cpp
        algorithms/modular-exp.cpp
        algorithms/mos-algorithm.cpp
        algorithms/ordering/nth-order-statistic.cpp
        algorithms/string/rabin-karp.cpp
#        algorithms/search.cpp
        algorithms/sieve-erastosthenes.cpp
        algorithms/ordering/sorting-rank.cpp
#        data-structures/SuffixArray1.cpp
        data-structures/suffix-array-2.cpp
        algorithms/string/pattern-search.cpp
        data-structures/disjoin-set.cpp
        data-structures/segment-tree-iter.cpp
        data-structures/segment-tree-rec.cpp
#        data-structures/suffixTree.cpp
        data-structures/trie.cpp
#        minLexicRotation.cpp
        util/util.h
        util/util.cpp
        util/matrix.cpp
        c++/hashing.cpp)

add_executable(MyLibrary ${SOURCE_FILES} algorithms/ordering/merge-sort.cpp)
add_executable(kth-element algorithms/ordering/kth-element.cpp ${SOURCE_FILES})
add_executable(binary-heap data-structures/binary-heap.cpp ${SOURCE_FILES})
add_executable(binary-heap-prio-update data-structures/binary-heap-prio-update.cpp ${SOURCE_FILES})
add_executable(op-overloading c++/op-overloading.cpp)
add_executable(func-templates c++/func-templates.cpp c++/multimap.cpp)
add_executable(misc-stl c++/misc-stl.cpp)