cmake_minimum_required(VERSION 2.8.4)
project(cpp)

add_executable(output output/main.cpp lib/graph/lca.h lib/collections/segment_tree.h lib/numbers/matrix.h
        lib/numbers/rational.h lib/string/suffix_automaton.h lib/collections/id.h lib/graph/algo/strongly_connected.h
        lib/numbers/primes.h lib/numbers/number_iterator.h lib/numbers/bigint.h lib/collections/fenwick.h
        lib/numbers/doubles.h lib/misc.h lib/range/range.h lib/range/rev_range.h lib/numbers/prime_fft.h
        lib/graph/dfs_order.h lib/collections/arr.h lib/collections/mdarr.h lib/collections/queue.h
        lib/collections/treap.h lib/collections/treap_set.h lib/collections/indexed_heap.h lib/graph/algo/mincost_flow.h
        lib/string/string_hash.h lib/graph/hl_decomposition.h lib/numbers/multiplicative_function.h
        lib/string/palindromes.h lib/numbers/bigmod.h lib/numbers/mod_numbers.h lib/collections/treap_multi_set.h
        lib/collections/md3arr.h lib/collections/md4arr.h lib/collections/ro_segment_tree.h
        lib/graph/algo/floyd_warshall.h lib/graph/algo/edge_distances.h lib/graph/algo/top_sort.h
        lib/graph/algo/centroid_decomposition.h lib/graph/edges/weighted_flow_edge.h lib/graph/edges/flow_edge.h
        lib/graph/edges/weighted_edge.h lib/graph/edges/biweighted_edge.h lib/graph/edges/biedge.h
        lib/graph/edges/base_edge.h lib/bits.h lib/geometry/point.h lib/geometry/base_geometry.h lib/geometry/line.h
        lib/geometry/circle.h lib/geometry/segment.h lib/geometry/polygon.h lib/recursive_function.h lib/chess.h
        lib/numbers/inf_int.h lib/string/string_utils.h lib/numbers/fwht.h)
add_executable(testrunner testrunner/main.cpp)

file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "lib/*.h" )
file(GLOB DIRECT "direct/*.cpp")

add_executable(task ${TASKS} ${HEADERS})
add_executable(direct "direct/main.cpp" ${HEADERS})
add_executable(gen "direct/gen.cpp" ${HEADERS})

ADD_DEFINITIONS(-static -std=c++17 -Wall -Wextra -Wno-sign-compare -Wno-reorder -Wno-logical-op-parentheses)

set_target_properties(task PROPERTIES LINKER_LANGUAGE CXX)
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ftrapping-math -g3 -gfull -ggdb -fno-inline-functions -fno-unroll-loops -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -DLOCAL -fsanitize=undefined -fsanitize-undefined-trap-on-error -fno-sanitize-recover=all -fstack-protector -fsanitize=address")
set (CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O0 -ftrapping-math -g3 -gfull -ggdb -fno-inline-functions -fno-unroll-loops -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -DLOCAL -D_FORTIFY_SOURCE=2 -DLOCAL -fsanitize-undefined-trap-on-error -fno-sanitize-recover=all -fstack-protector -fsanitize=address")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DLOCAL_RELEASE")
