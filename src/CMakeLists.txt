
set(STANDARD_FLAGS "-g -Wall -std=c++11")

add_library(heuristic_dump heuristic_dump.cpp)
add_library(heuristic_1 heuristic_1.cpp)
add_library(heuristic_2 heuristic_2.cpp)

set(CMAKE_CXX_FLAGS "${STANDARD_FLAGS} -D HEURISTIK_0")
add_executable(r-spantree_0 main.cpp)
target_link_libraries(r-spantree_0 heuristic_dump)

set(CMAKE_CXX_FLAGS "${STANDARD_FLAGS} -D HEURISTIK_1")
add_executable(r-spantree_1 main.cpp)
target_link_libraries(r-spantree_1 heuristic_1)

set(CMAKE_CXX_FLAGS "${STANDARD_FLAGS} -D HEURISTIK_2")
add_executable(r-spantree_2 main.cpp)
target_link_libraries(r-spantree_2 heuristic_2)
