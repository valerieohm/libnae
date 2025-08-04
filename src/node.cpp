#include <node.h>
namespace nae {
Obj::~Obj() = default;
Node::~Node() {}

class NodeImpl : public Node {
 public:
  NodeImpl(std::string const &name) : Node(name) {}
};

std::shared_ptr<Node> createNode(std::string const &name) {
  return std::make_shared<NodeImpl>(name);
}
}  // namespace nae