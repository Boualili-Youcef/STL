#ifndef GRAPH_EDGE_HPP
#define GRAPH_EDGE_HPP

#include <memory>
#include <string>
#include <utility>

class Graph;

class Vertex;

class Edge {
public:
  Edge(std::string id, unsigned int length) : _id(std::move(id)), _length(length) {}

  const std::string &id() const { return _id; }

  unsigned int length() const { return _length; }

  const std::weak_ptr<Vertex> &in_vertex() const { return _in_vertex; }

  const std::weak_ptr<Vertex> &out_vertex() const { return _out_vertex; }

  virtual ~Edge() = default;

private:
  friend class Graph;

  void set_in_vertex(const std::weak_ptr<Vertex> &in_vertex) { _in_vertex = in_vertex; }

  void set_out_vertex(const std::weak_ptr<Vertex> &out_vertex) { _out_vertex = out_vertex; }

  std::string _id;
  unsigned int _length;
  std::weak_ptr<Vertex> _in_vertex;
  std::weak_ptr<Vertex> _out_vertex;
};

#endif //GRAPH_EDGE_HPP
