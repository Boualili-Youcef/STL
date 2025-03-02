#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP

#include "edge.hpp"
#include "vertex.hpp"

#include <map>
#include <vector>
#include <limits>
#include <queue>

class Graph
{
public:
  // Ici utilisation d'alias pour les types de données
  // C'est des tableaux associatifs (map) qui associent une clé (string) à une valeur (shared_ptr)
  using Edges = std::map<std::string, std::shared_ptr<Edge>>;
  using Vertices = std::map<std::string, std::shared_ptr<Vertex>>;

  // Constructeur par défaut
  Graph() = default;

  // Ca permet d'ajouter un arc au dictionnaire _edges
  void add_edge(const std::shared_ptr<Edge> &edge);

  void add_vertex(const std::shared_ptr<Vertex> &vertex);

  const Edges &edges() const { return _edges; }

  std::shared_ptr<Vertex> end(const std::string &generator_id) const;

  std::shared_ptr<Vertex> generator(const std::string &end_id) const;

  const Vertices &vertices() const { return _vertices; }

  // search_shortest_path
  // TODO: A voir si vaut mieux retourner un vector de Vertices ou de shared_ptr<Vertex>

  const std::vector<std::shared_ptr<Vertex>> search_shortest_path(const std::string &source, const std::string &destination) const;

  virtual ~Graph() = default;

protected:
  Edges _edges;
  Vertices _vertices;
};

#endif // GRAPH_GRAPH_HPP
