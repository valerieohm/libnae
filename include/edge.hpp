#ifndef EDGE_H
#define EDGE_H

#include <memory>
#include <obj.hpp>
#include <vector>
namespace nae {
class Edge : public Obj, public std::enable_shared_from_this<Edge> {
public:
    Edge(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
         std::string const &name, bool directed = false);
    std::shared_ptr<Obj> getOther(std::shared_ptr<Obj> vertex) const;
    std::shared_ptr<Obj> getOther(std::string const &vertex_name) const;
    virtual ~Edge();
    std::shared_ptr<Obj> getSrc() const { return src; }
    std::shared_ptr<Obj> getDst() const { return dst; }
    bool isDirected() const { return directed; }
    void setDirected(bool swap);
    void unsetDirected() { directed = false; }
    void swap();

private:
    Edge() = delete; // Prevent default constructor

    bool directed;
    int weight = 1;
    int used = 0;
    std::shared_ptr<Obj> src;
    std::shared_ptr<Obj> dst;
};

std::shared_ptr<Edge> createEdge(std::shared_ptr<Obj> vertex_src,
                                 std::shared_ptr<Obj> vertex_dst,
                                 std::string const &name,
                                 bool directed = false);
} // namespace nae

#endif // EDGE_H