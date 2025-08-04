#ifndef NODE_H
#define NODE_H
#include <memory>

#include "libnae.h"
namespace nae {
class Node : public Obj {
    public:
    Node(std::string const& name) : Obj(Type::Node, name) {}
    virtual ~Node() = 0;
};

std::shared_ptr<Node> createNode(std::string const& name);
}

#endif // NODE_H