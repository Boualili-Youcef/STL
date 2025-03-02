#include "graph.hpp"
#include "loader.hpp"

#include <algorithm>
#include <iostream>

int main()
{
  Graph graph;
  Loader loader("../../data/calais.json");

  loader.load(graph);

  std::cout << "All vertex number: " << graph.vertices().size() << std::endl;
  std::cout << "Input vertex number: "
            << std::count_if(graph.vertices().cbegin(), graph.vertices().cend(),
                             [](const auto &e)
                             { return e.second->type() == Vertex::INPUT; })
            << std::endl;
  std::cout << "Output vertex number: "
            << std::count_if(graph.vertices().cbegin(), graph.vertices().cend(),
                             [](const auto &e)
                             { return e.second->type() == Vertex::OUTPUT; })
            << std::endl;
  std::cout << "Internal vertex number: "
            << std::count_if(graph.vertices().cbegin(), graph.vertices().cend(),
                             [](const auto &e)
                             { return e.second->type() == Vertex::INTERNAL; })
            << std::endl;
  std::cout << "Edge number: " << graph.edges().size() << std::endl;

  auto path = graph.search_shortest_path("generator/507", "end/366");
  for (const auto &e : path)
  {
    std::cout << e << " ";
  }
  std::cout << std::endl;

  return 0;

  return 0;
}