#ifndef VERTEX_H
#define VERTEX_H
#include <memory>
#include <vector>

#include <obj.hpp>
namespace nae {
class Vertex : public Obj, public std::enable_shared_from_this<Vertex> {
public:
    explicit Vertex(std::string const &name, int cost) : Obj(Type::Vertex, name, cost) {
        userIntField = INT64_MAX;
    }
    void addEdge(std::shared_ptr<Obj> edge) { edges.push_back(edge); }
    std::vector<std::shared_ptr<Obj>> getEdges() const { return edges; }
    virtual ~Vertex();

public:
    int64_t getDistance() const { return getUserIntField(); }
    void setDistance(int64_t dist) { setUserIntField(dist); }
    void resetDistance() { setUserIntField(INT64_MAX); }
    std::shared_ptr<Vertex> getPrevious();
    void setPrevious(std::shared_ptr<Vertex> vertex) {
        setUserObjectField(vertex);
    }
    void resetPrevious() { return setPrevious(nullptr); }

private:
    std::vector<std::shared_ptr<Obj>> edges;
    Vertex() = delete; // Prevent default constructor
};

std::shared_ptr<Vertex> createVertex(std::string const &name, int cost);
} // namespace nae

#endif // VERTEX_H