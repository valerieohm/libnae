#include <obj.h>
#include <vertex.h>
namespace nae {
Vertex::~Vertex() {}

class NodeImpl : public Vertex {
 public:
  NodeImpl(std::string const &name) : Vertex(name) {}
};

std::shared_ptr<Vertex> createNode(std::string const &name) {
  return std::make_shared<NodeImpl>(name);
}
}  // namespace nae