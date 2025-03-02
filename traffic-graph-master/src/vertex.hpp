#ifndef GRAPH_VERTEX_HPP
#define GRAPH_VERTEX_HPP

#include <memory>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

class Edge;

using Edges = std::vector<std::weak_ptr<Edge>>;

class Vertex {
public:
  enum Type {
    INPUT, OUTPUT, INTERNAL
  };

  Vertex(std::string id, Type type, Edges in_edges, Edges out_edges);

  const std::string &id() const { return _id; }

  const Edges &in_edges() const { return _in_edges; }

  const Edges &out_edges() const { return _out_edges; }

  const Type &type() const { return _type; }

  virtual ~Vertex() = default;

private:
  std::string _id;
  Type _type;
  Edges _out_edges;
  Edges _in_edges;
};

#endif //GRAPH_VERTEX_HPP
