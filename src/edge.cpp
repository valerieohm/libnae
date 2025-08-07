#include <obj.h>
#include <edge.h>
#include <vertex.h>

#include <stdexcept>
namespace nae {
Edge::~Edge() {}

Edge::Edge(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
           std::string const &name)
    : Obj(Type::Edge, name) {
    vertexes.push_back(vertex_src);
    vertexes.push_back(vertex_dst);

  try {
    auto s = std::dynamic_pointer_cast<Vertex>(vertex_src);
    s->addEdge(shared_from_this());
  } catch (const std::bad_cast &e) {
    throw std::runtime_error("vertex_src is not a Vertex: " + std::string(e.what()));
    // Handle the case where vertex_src is not a Vertex
  }
  try {
    auto d = std::dynamic_pointer_cast<Vertex>(vertex_dst);
    d->addEdge(shared_from_this());
  } catch (const std::bad_cast &e) {
    throw std::runtime_error("vertex_dst is not a Vertex: " + std::string(e.what()));
    // Handle the case where vertex_dst is not a Vertex
  }

}

std::shared_ptr<Obj> Edge::getOtherVertex(std::shared_ptr<Obj> vertex) const {
    if (vertexes.size() != 2) {
        throw std::runtime_error("Edge must have exactly two vertexes.");
    }
    if (vertex == vertexes[0]) {
        return vertexes[1];
    } else if (vertex == vertexes[1]) {
        return vertexes[0];
    } else {
        throw std::runtime_error("Provided vertex is not part of this edge.");
    }
}
class EdgeImpl : public Edge {
 public:
  EdgeImpl(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
           std::string const &name)
      : Edge(vertex_src, vertex_dst, name) {}
};

std::shared_ptr<Edge> createEdge(std::shared_ptr<Obj> vertex_src,
                                 std::shared_ptr<Obj> vertex_dst,
                                 std::string const& name) {
    return std::make_shared<EdgeImpl>(vertex_src, vertex_dst, name);
;
}
}  // namespace nae