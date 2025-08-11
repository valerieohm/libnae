#include <obj.hpp>
#include <vertex.hpp>
namespace nae {
Vertex::~Vertex() {}

class VertexImpl : public Vertex {
 public:
  VertexImpl(std::string const &name) : Vertex(name) {}
};

std::shared_ptr<Vertex> createVertex(std::string const &name) {
  return std::make_shared<VertexImpl>(name);
}
}  // namespace nae