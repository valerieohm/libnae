#ifndef EDGE_H
#define EDGE_H

#include <memory>
#include <vector>
#include <obj.h>
namespace nae {
class Edge : public Obj, public std::enable_shared_from_this<Edge> {
    public:
    Edge(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
         std::string const& name);
         std::shared_ptr<Obj> getOtherVertex(std::shared_ptr<Obj> vertex) const;
    virtual ~Edge();
    std::shared_ptr<Obj> getSource() const { return vertexes[0]; }
    std::shared_ptr<Obj> getDestination() const { return vertexes[1]; }
    private:
    Edge() = delete;  // Prevent default constructor
    //Edge(std::string const& name) : Obj(Type::Edge, name) {}
    std::vector<std::shared_ptr<Obj>> vertexes;
};

std::shared_ptr<Edge> createEdge(std::shared_ptr<Obj> vertex_src,
                                 std::shared_ptr<Obj> vertex_dst,
                                 std::string const& name);
}

#endif // EDGE_H