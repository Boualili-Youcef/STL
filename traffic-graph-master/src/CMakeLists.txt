include_directories(${CMAKE_SOURCE_DIR}/src)

link_directories()

set(graph_hpp edge.hpp graph.hpp loader.hpp vertex.hpp)

set(graph_cpp graph.cpp loader.cpp vertex.cpp)

add_library(graph ${graph_hpp} ${graph_cpp})

target_link_libraries(graph)

add_executable(main main.cpp)

target_link_libraries(main graph)