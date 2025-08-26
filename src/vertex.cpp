#include <obj.hpp>
#include <vertex.hpp>
namespace nae {
Vertex::~Vertex() {}

std::shared_ptr<Vertex> Vertex::getPrevious() {
    if (getUserObjectField()) {
        if (auto v = std::dynamic_pointer_cast<Vertex>(getUserObjectField())) {
            if (v)
                return v;
        }
    }
    return nullptr;
}

class VertexImpl : public Vertex {
 public:
  VertexImpl(std::string const &name, int cost) : Vertex(name, cost) {}
};

std::shared_ptr<Vertex> createVertex(std::string const &name, int cost) {
  return std::make_shared<VertexImpl>(name, cost);
}
}  // namespace nae