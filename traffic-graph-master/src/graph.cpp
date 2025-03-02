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

const std::vector<std::string> Graph::search_shortest_path(const std::string &source, const std::string &destination) const
{
  // Taille du graphe:
  unsigned int n = vertices().size();
  // Pour plus l'infini vu que c'est des int donc on prend la valeur max je separe pour mieux comprendre
  unsigned int inf = std::numeric_limits<unsigned int>::max();
  // J'utilise un map pour stocker les sommets et leur score
  std::map<std::string, unsigned int> score;
  for (const auto &vertex : vertices())
  {
    score[vertex.first] = inf;
  }

  // from[i]=plus proche voisin connu pour tout i telque i est un sommet
  // Un map : clé = sommet, valeur = sommet le plus proche
  std::map<std::string, std::shared_ptr<Vertex>> from;

  // Liste des sommets en cours de traitement
  std::queue<std::string> queue;

  score[source] = 0;

  // ajout de sourrce dans la queue
  queue.push(source);

  // On parcourt la queue
  while (!queue.empty())
  {
    std::string courant = queue.front();
    queue.pop();
    if (courant == destination)
    {
      // chemin = liste vide
      std::vector<std::string> chemin;
      while (courant != source)
      {
        // Placer courant dans chemin
        chemin.push_back(courant);
        courant = from[courant]->id();
      }
      // Placer source dans chemin
      chemin.push_back(source);
      // Inverser chemin
      std::reverse(chemin.begin(), chemin.end()); // TODO :ici c'est plus efficace avec une list ou stack a voir si on peut changer
      return std::move(chemin);                   // utilisation de la move semantic pour eviter la copie
    }
  }

  for (const auto &vertex : vertices())
  {
    for (const auto &edge : vertex.second->out_edges())
    {
      // ca retourne un weak_ptr donc on le lock pour avoir un shared_ptr
      std::shared_ptr<Vertex> out_vertex = edge.lock()->out_vertex().lock(); // out car c'est la ou on va
      if (out_vertex != nullptr)
      {
        // La on cherche le plus proche voisin donc
        unsigned int distance = edge.lock()->length();

        from[out_vertex->id()] = vertex.second;
      }
    }
  }

  Graph::Vertices::const_iterator it = vertices().find(source);
  if (it != vertices().end())
  {
    from[source] = nullptr;
  }
}