#ifndef VERTEX_H
#define VERTEX_H
#include <memory>
#include <vector>

#include <obj.hpp>
namespace nae {
class Vertex : public Obj, public std::enable_shared_from_this<Vertex> {
public:
    explicit Vertex(std::string const &name)
        : Obj(Type::Vertex, name), distance(INT64_MAX) {}
    void addEdge(std::shared_ptr<Obj> edge) { edges.push_back(edge); }
    std::vector<std::shared_ptr<Obj>> getEdges() const { return edges; }
    virtual ~Vertex();

public:
    int64_t getDistance() const { return distance; }
    void setDistance(int64_t dist) { distance = dist; }
    void resetDistance() { distance = INT64_MAX; }

private:
    int64_t distance;
    std::vector<std::shared_ptr<Obj>> edges;
    Vertex() = delete; // Prevent default constructor
};

std::shared_ptr<Vertex> createVertex(std::string const &name);
} // namespace nae

#endif // VERTEX_H