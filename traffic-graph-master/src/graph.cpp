#include "graph.hpp"

void Graph::add_edge(const std::shared_ptr<Edge> &edge)
{
  _edges[edge->id()] = edge;
}

void Graph::add_vertex(const std::shared_ptr<Vertex> &vertex)
{
  _vertices[vertex->id()] = vertex;
  for (const auto &e : vertex->in_edges())
  {
    e.lock()->set_out_vertex(vertex);
  }
  for (const auto &e : vertex->out_edges())
  {
    e.lock()->set_in_vertex(vertex);
  }
}

std::shared_ptr<Vertex> Graph::end(const std::string &generator_id) const
{
  auto v = _vertices.find(generator_id);

  if (v != _vertices.cend())
  {
    std::string edge_id = v->second->out_edges()[0].lock()->id();
    std::string reverse_edge_id =
        edge_id[edge_id.size() - 2] == 'R' ? edge_id.substr(edge_id.size() - 3) : edge_id + "_R";
    auto e = _edges.find(reverse_edge_id);

    if (e != _edges.cend())
    {
      std::string end_id = e->second->out_vertex().lock()->id();

      return _vertices.find(end_id)->second;
    }
  }
  return nullptr;
}

std::shared_ptr<Vertex> Graph::generator(const std::string &end_id) const
{
  auto v = _vertices.find(end_id);

  if (v != _vertices.cend())
  {
    std::string edge_id = v->second->in_edges()[0].lock()->id();
    std::string reverse_edge_id =
        edge_id[edge_id.size() - 1] == 'R' ? edge_id.substr(0, edge_id.size() - 2) : edge_id + "_R";
    auto e = _edges.find(reverse_edge_id);

    if (e != _edges.cend())
    {
      std::string generator_id = e->second->in_vertex().lock()->id();

      return _vertices.find(generator_id)->second;
    }
  }
  return nullptr;
}

const std::vector<std::shared_ptr<Vertex>> Graph::search_shortest_path(const std::string &source, const std::string &destination) const
{
  // Taille du graphe:
  unsigned int n = vertices().size();
  // Pour plus l'infini vu que c'est des int donc on prend la valeur max je separe pour mieux comprendre
  unsigned int inf = std::numeric_limits<unsigned int>::max();
  std::vector<unsigned int> score(n, inf);
}