#include <obj.hpp>
#include <edge.hpp>
#include <vertex.hpp>

#include <stdexcept>
namespace nae {
Edge::~Edge() {}

Edge::Edge(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
           std::string const &name, bool directed)
    : Obj(Type::Edge, name),
      directed(directed),
      src(vertex_src),
      dst(vertex_dst) {}

std::shared_ptr<Obj> Edge::getOther(std::shared_ptr<Obj> vertex) const {
    auto vert = std::dynamic_pointer_cast<Vertex>(vertex);
    if (!vert) {
      throw std::runtime_error("getOther(std::shared_ptr<Obj>) null obj");
    }
    if (vertex == src) return dst;
    if (vertex == dst) return src;
    // If the vertex is not one of the two, throw an error
    throw std::runtime_error("getOther(std::shared_ptr<Obj>) mismatch");
    return nullptr;
}

std::shared_ptr<Obj> Edge::getOther(std::string const & vertex_name) const {
    if (src->getName() == vertex_name) return dst;
    if (dst->getName() == vertex_name) return src;
    throw std::runtime_error("getOther(std::string) mismatch");
    return nullptr;
}

void Edge::setDirected(bool swap) {
    if (swap) {
        this->swap();
    }
    directed = true;
}

void Edge::swap() {
    std::swap(src, dst);
}

std::string Edge::toString() const {
    std::string result = "Edge name: " + getName() + " s:" + src->getName();
    if (directed)
        result += " > ";
    else
        result += " - ";

    result +=
        "d:" + dst->getName() + " userIntField:" + std::to_string(userIntField);
    if (userObjField != nullptr) {
        result += " userObjectField:" + userObjField->getName();
    } else {
        result += " userObjectField: null";
    }
    return result;
}

class EdgeImpl : public Edge {
 public:
  EdgeImpl(std::shared_ptr<Obj> vertex_src, std::shared_ptr<Obj> vertex_dst,
           std::string const &name, bool directed)
      : Edge(vertex_src, vertex_dst, name, directed) {}
};

std::shared_ptr<Edge> createEdge(std::shared_ptr<Obj> vertex_src,
                                 std::shared_ptr<Obj> vertex_dst,
                                 std::string const& name, bool directed) {
    auto edge = std::make_shared<EdgeImpl>(vertex_src, vertex_dst, name, directed);
    auto s = std::dynamic_pointer_cast<Vertex>(vertex_src);
    s->addEdge(edge);
    auto d = std::dynamic_pointer_cast<Vertex>(vertex_dst);
    d->addEdge(edge);
    return edge;
}
}  // namespace nae