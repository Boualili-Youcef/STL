#include "vertex.hpp"

Vertex::Vertex(std::string id, Type type, Edges in_edges, Edges out_edges) :
  _id(std::move(id)), _type(type), _in_edges(std::move(in_edges)), _out_edges(std::move(out_edges)) {}
