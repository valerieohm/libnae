#include <graph.h>

#include <fstream>
#include <memory>
#include <sstream>
#include <unordered_map>

namespace nae {

std::shared_ptr<Graph> createGraph(std::string const &infile_name) {
  return std::make_shared<Graph>(infile_name);
}

std::shared_ptr<Vertex> Graph::addVertex(std::string const &name) {
  auto v = createVertex(name);
  vmap_.insert(name, v);
  return v;
}
std::shared_ptr<Edge> Graph::addEdge(std::string const &src,
                                     std::string const &dst,
                                     std::string const &name) {
  auto srcv = findVertex(src);
  auto dstv = findVertex(dst);
  auto e = createEdge(srcv, dstv, name);
  emap_.insert(name, e);
  return e;
}

std::shared_ptr<Vertex> Graph::findVertex(std::string const &name) {
  if (auto search = vmap_.find(name); search != vmap_.end())
    return search->second;
  return nullptr;
}

std::shared_ptr<Edge> Graph::findEdge(std::string const &name) {
  if (auto search = emap_.find(name); search != emap_.end())
    return search->second;
  return nullptr;
}
bool Graph::parse() {
  std::shared_ptr<Graph> self = shared_from_this();
  return parser.parse(self);
}

std::string Graph::unparse() {
  std::ostringstream oss;
  oss << "#NAE_0.1\n";
  oss << "#VERTICIES\n";
  for (size_t i = 0; i < vmap_.size(); ++i) {
    oss << vmap_.atOrder(i)->getName() << "\n";
  }
  oss << "#EDGES\n";
  for (size_t i = 0; i < emap_.size(); ++i) {
    auto edge = emap_.atOrder(i);
    oss << edge->getName() << " " << edge->getSource()->getName() <<
        " - "<< edge->getDestination()->getName() << "\n";
  }
  return oss.str();
}
}  // namespace nae