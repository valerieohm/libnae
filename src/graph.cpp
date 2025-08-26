#include <graph.hpp>

#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>

namespace nae {

std::shared_ptr<Graph> createGraph(std::string const &infile_name) {
  return std::make_shared<Graph>(infile_name);
}

std::shared_ptr<Vertex> Graph::addVertex(std::string const &name, int cost) {
  auto v = createVertex(name,cost);
  vmap_.emplace(name, v);
  return v;
}
std::shared_ptr<Edge> Graph::addEdge(std::string const &src,
                                     std::string const &dst,
                                     std::string const &name, int cost) {
  auto srcv = findVertex(src);
  auto dstv = findVertex(dst);
  auto e = createEdge(srcv, dstv, name, false, cost);
  emap_.emplace(name, e);
  return e;
}

std::shared_ptr<Vertex> Graph::findVertex(std::string const &name) {
  if (auto search = vmap_.find(name); search != vmap_.end())
    return search->second;
  throw std::runtime_error("findVertex(std::string) failed");
  return nullptr;
}

std::shared_ptr<Edge> Graph::findEdge(std::string const &name) {
  if (auto search = emap_.find(name); search != emap_.end())
    return search->second;
  throw std::runtime_error("findEdge(std::string) failed");
}
bool Graph::parse() {
  std::shared_ptr<Graph> self = shared_from_this();
  return parser.parse(self);
}

std::string Graph::unparse() {
  std::ostringstream oss;
  oss << "graph G {\n";

  // Output vertices with attributes
  for (const auto &pair : vmap_) {
      auto vertex = pair.second;
      oss << "    " << vertex->getName() << " [cost=" << vertex->getCost();

      // Add position if available
      std::string pos = vertex->getUserStringField();
      if (!pos.empty()) {
          oss << ", pos=\"" << pos << "!\"";
      }

      oss << "]\n";
  }

  oss << "\n";

  // Output edges with attributes
  for (const auto &pair : emap_) {
      auto edge = pair.second;
      auto src = std::dynamic_pointer_cast<Vertex>(edge->getSrc());
      auto dst = std::dynamic_pointer_cast<Vertex>(edge->getDst());

      if (src && dst) {
          oss << "    " << src->getName() << " -- " << dst->getName();
          oss << " [label=\"" << edge->getName()
              << "\", cost=" << edge->getCost() << "]\n";
      }
  }

  oss << "}\n";
  return oss.str();
}
}  // namespace nae