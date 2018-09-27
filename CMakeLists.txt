cmake_minimum_required(VERSION 3.7)
project(MyLibrary)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
#        algorithms/DP/fibonacci/fibonacci/fib_n.cpp
#        algorithms/DP/longest_common_subseq/longest_common_subseq/LCS.cpp
#        algorithms/DP/longest_inc_subseq/longest_inc_subseq/lis.cpp
#        algorithms/DP/quine/quine/quine.cpp
        algorithms/bellman-ford.cpp
        algorithms/dijkstra.cpp
        algorithms/FFT.cpp
        algorithms/FFTRecursive.cpp
        algorithms/floyd-warshall.cpp
        algorithms/graph-algorithms.cpp
        algorithms/KMP.cpp
        algorithms/kth-element.cpp
        algorithms/manacher.cpp
        algorithms/max-flow.cpp
        algorithms/min-cost-flow.cpp
        algorithms/mos-algorithm.cpp
        algorithms/nth-order-statistic.cpp
        algorithms/rabin-karp.cpp
#        algorithms/Search.cpp
        algorithms/sieve-erastosthenes.cpp
        algorithms/sorting.cpp
#        data-structures/SuffixArray1.cpp
        data-structures/SuffixArray2.cpp
        algorithms/z-algorithm.cpp
        data-structures/DisjointSet.cpp
        data-structures/SegmentTreeIter.cpp
        data-structures/SegmentTreeRec.cpp
#        data-structures/suffixTree.cpp
        data-structures/Trie.cpp
#        minLexicRotation.cpp
        util/util.h util/util.cpp util/matrix.cpp algorithms/modular-exp.cpp data-structures/binary-heap.cpp data-structures/binary-heap-prio-update.cpp)

add_executable(MyLibrary ${SOURCE_FILES})