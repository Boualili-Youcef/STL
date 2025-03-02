#ifndef TRAFFIC_LOADER_HPP
#define TRAFFIC_LOADER_HPP

#include <string>
#include "nlohmann/json.hpp"

#include "graph.hpp"

class Loader {
public:
  Loader(const std::string &file_name);

  void load(Graph &graph);

private:
  nlohmann::json _data;
};

#endif //TRAFFIC_LOADER_HPP
