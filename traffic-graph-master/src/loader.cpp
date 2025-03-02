#include "loader.hpp"
#include "edge.hpp"
#include "vertex.hpp"

#include <fstream>
#include <iostream>

Loader::Loader(const std::string &file_name) {
  std::ifstream input(file_name);

  if (input) {
    const std::string str((std::istreambuf_iterator<char>(input)),
                          std::istreambuf_iterator<char>());

    _data = nlohmann::json::parse(str);
  } else {
    std::cerr << input.fail() << std::endl;
  }
}

void Loader::load(Graph &graph) {
  std::map<std::string, size_t> in_link_number;
  std::map<std::string, size_t> out_link_number;
  std::map<std::string, std::shared_ptr<Edge>> edges;
  std::map<std::string, std::shared_ptr<Vertex>> vertices;

  for (const auto &link: _data["links"]) {
    std::shared_ptr<Edge> new_link;

    new_link = std::make_shared<Edge>(link["id"].get<std::string>(), link["length"].get<unsigned int>());

    graph.add_edge(new_link);
    edges[new_link->id()] = new_link;
    if (in_link_number.find(link["output_ids"][0].get<std::string>()) == in_link_number.end()) {
      in_link_number[link["output_ids"][0].get<std::string>()] = 1;
    } else {
      in_link_number[link["output_ids"][0].get<std::string>()]++;
    }
    if (out_link_number.find(link["input_ids"][0].get<std::string>()) == in_link_number.end()) {
      out_link_number[link["input_ids"][0].get<std::string>()] = 1;
    } else {
      out_link_number[link["input_ids"][0].get<std::string>()]++;
    }
  }
  for (const auto &node: _data["inputs"]) {
    std::shared_ptr<Vertex> new_node;
    std::string node_id = node["id"].get<std::string>();
    Edges out_edges(out_link_number[node_id]);

    if (node.contains("output_ids")) {
      unsigned int index = 0;

      for (const auto &out_edge: node["output_ids"]) {
        out_edges[index++] = edges[out_edge.get<std::string>()];
      }
    }
    new_node = std::make_shared<Vertex>(node_id, Vertex::INPUT, Edges{}, out_edges);
    graph.add_vertex(new_node);
    vertices[node_id] = new_node;
  }
  for (const auto &node: _data["outputs"]) {
    std::shared_ptr<Vertex> new_node;
    std::string node_id = node["id"].get<std::string>();
    Edges in_edges(in_link_number[node_id]);

    if (node.contains("input_ids")) {
      unsigned int index = 0;

      for (const auto &in_edge: node["input_ids"]) {
        in_edges[index++] = edges[in_edge.get<std::string>()];
      }
    }
    new_node = std::make_shared<Vertex>(node_id, Vertex::OUTPUT, in_edges, Edges{});
    graph.add_vertex(new_node);
    vertices[node_id] = new_node;
  }
  for (const auto &node: _data["junctions"]) {
    std::shared_ptr<Vertex> new_node;
    std::string node_id = node["id"].get<std::string>();
    Edges in_edges(in_link_number[node_id]);
    Edges out_edges(out_link_number[node_id]);

    if (node.contains("input_ids")) {
      unsigned int index = 0;

      for (const auto &in_edge: node["input_ids"]) {
        in_edges[index++] = edges[in_edge.get<std::string>()];
      }
    }
    if (node.contains("output_ids")) {
      unsigned int index = 0;

      for (const auto &out_edge: node["output_ids"]) {
        out_edges[index++] = edges[out_edge.get<std::string>()];
      }
    }
    new_node = std::make_shared<Vertex>(node_id, Vertex::INTERNAL, in_edges, out_edges);
    graph.add_vertex(new_node);
    vertices[node_id] = new_node;
  }
}