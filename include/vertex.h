#ifndef VERTEX_H
#define VERTEX_H
#include <memory>
#include <vector>

#include <obj.h>
namespace nae {
class Vertex : public Obj, public std::enable_shared_from_this<Vertex> {
    public:
    explicit Vertex(std::string const& name) : Obj(Type::Node, name) {}
    void addEdge(std::shared_ptr<Obj> edge) { edges.push_back(edge); }
    std::vector<std::shared_ptr<Obj>> getEdges() const { return edges; }
    virtual ~Vertex() = 0;
    private:

    std::vector<std::shared_ptr<Obj>> edges;
    Vertex() = delete;  // Prevent default constructor
};

std::shared_ptr<Vertex> createNode(std::string const& name);
}

#endif // VERTEX_H