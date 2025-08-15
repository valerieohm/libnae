#include <algorithms.hpp>
#include <edge.hpp>
#include <functional>
#include <graph.hpp>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>
#include <vertex.hpp>

namespace nae {

bool Algorithms::findShortestPath(std::shared_ptr<Graph> graph,
                                  std::shared_ptr<Vertex> start,
                                  std::shared_ptr<Vertex> end) {
    // Implement the logic to find the shortest path between start and end
    // vertices This is a placeholder implementation
    if (!graph || !start || !end) {
        return false; // Invalid input
    }

    std::priority_queue<
        std::shared_ptr<Vertex>, std::vector<std::shared_ptr<Vertex>>,
        std::function<bool(std::shared_ptr<Vertex>, std::shared_ptr<Vertex>)>>
        queue([](std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b) {
            return a->getDistance() > b->getDistance();
        });

    auto showQueue = [&queue]() {
        // Create a temporary copy to iterate
        auto temp_queue = queue;
        while (!temp_queue.empty()) {
            auto v = temp_queue.top();
            std::cout << v->toString() << std::endl;
            temp_queue.pop();
        }
    };

    for (auto it = graph->vertexBegin(); it != graph->vertexEnd(); ++it) {
        it->second->resetDistance(); // Reset distances for all vertices
        it->second->resetPrevious();
        queue.push(it->second);
    }

    // showQueue();

    while (!queue.empty()) {
        auto u = queue.top();
        queue.pop();
        std::cout << "top: " << u->toString() << std::endl;
        for (const auto &edge : u->getEdges()) {
            std::cout << edge->toString() << std::endl;
        }
    }
    // showQueue();
    return true;
}
}; // namespace nae
