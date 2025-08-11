#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <graph.hpp>

namespace nae {

class Algorithms {
public:
  static bool findShortestPath(std::shared_ptr<Graph> graph,
                               std::shared_ptr<Vertex> start,
                               std::shared_ptr<Vertex> end);
};

} // namespace nae
#endif