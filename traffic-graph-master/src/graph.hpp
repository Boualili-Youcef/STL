#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP

#include "edge.hpp"
#include "vertex.hpp"

#include <map>
#include <vector>

class Graph {
public:
  using Edges = std::map<std::string, std::shared_ptr<Edge>>;
  using Vertices = std::map<std::string, std::shared_ptr<Vertex>>;

  Graph() = default;

  void add_edge(const std::shared_ptr<Edge> &edge);

  void add_vertex(const std::shared_ptr<Vertex> &vertex);

  const Edges &edges() const { return _edges; }

  std::shared_ptr<Vertex> end(const std::string &generator_id) const;

  std::shared_ptr<Vertex> generator(const std::string &end_id) const;

  const Vertices &vertices() const { return _vertices; }

  virtual ~Graph() = default;

protected:
  Edges _edges;
  Vertices _vertices;
};

#endif //GRAPH_GRAPH_HPP
