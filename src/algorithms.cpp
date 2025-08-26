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

    std::vector<std::shared_ptr<Vertex>> queue;

    auto showQueue = [&queue]() {
        // Create a temporary copy to iterate
        std::cout <<"--"<<std::endl;
        for (auto vp : queue) {
            std::cout << vp->toString() << std::endl;
        }
        std::cout <<"--"<<std::endl;
    };

    graph->forEachVertex([&start, &queue](auto &v) {
        v->resetDistance(); // Reset distances for all vertices
        v->resetPrevious();
        if (v == start) v->setDistance(0);
        queue.push_back(v);
    });

    //showQueue();

    while (!queue.empty()) {
        std::stable_sort(
            queue.begin(), queue.end(),
            [](std::shared_ptr<Vertex> a, std::shared_ptr<Vertex> b) {
                return a->getDistance() < b->getDistance();
            });

        //showQueue();
        auto u = *(queue.begin());
        queue.erase(queue.begin());
        std::cout << "Top: " << u->toString() << std::endl;
        for (const auto &eobj : u->getEdges()) {
            auto edge = std::dynamic_pointer_cast<Edge>(eobj);
            auto oobj = edge->getOther(u->getName());
            auto v = std::dynamic_pointer_cast<Vertex>(oobj);
            auto alt = u->getDistance() + edge->getCost();
            std::cout << "path thru " << edge->getName() << " to "
                      << v->getName() << " alt=" << alt
                      << " dist=" << v->getDistance() << std::endl;
            if (alt < v->getDistance()) {
                v->setDistance(alt);
                v->setPrevious(u);
            }
        }
        //showQueue();
    }
    showQueue();
    auto vx = end;
    while (vx) {
        std::cout << "e:" << vx->getName() << " d=" << vx->getDistance() << " p=" << (vx->getPrevious() ? vx->getPrevious()->getName(): std::string("null")) << std::endl;
        vx = vx->getPrevious();
    }
    return true;
}
}; // namespace nae
