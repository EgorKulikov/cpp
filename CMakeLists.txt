cmake_minimum_required(VERSION 2.8.4)
project(cpp)

add_executable(output output/main.cpp lib/graph/lca.h lib/collections/interval_tree.h lib/numbers/matrix.h lib/numbers/rational.h lib/string/suffix_automaton.h lib/collections/id.h lib/graph/misc_algo.h lib/numbers/primes.h lib/collections/vector_dsu.h lib/geometry.h lib/numbers/number_iterator.h lib/numbers/bigint.h lib/collections/fenwick.h lib/numbers/doubles.h lib/misc.h lib/range/range.h lib/range/rev_range.h lib/collections/vector.h lib/numbers/prime_fft.h)
add_executable(testrunner testrunner/main.cpp)
file(GLOB TASKS "tasks/*.cpp")
file(GLOB_RECURSE HEADERS "lib/*.h" )

ADD_DEFINITIONS(-std=c++14)

add_executable(test ${TASKS} ${HEADERS})
#add_executable(direct direct/main.c)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLOCAL")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DLOCAL")
