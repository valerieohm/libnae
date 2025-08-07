#define BOOST_TEST_MODULE LibNaeTest
#include <boost/test/included/unit_test.hpp>
#include <vertex.h>
#include <edge.h>

#include <memory>

using namespace nae;

BOOST_AUTO_TEST_CASE(vertex_creation)
{
    std::vector<std::shared_ptr<Vertex>> vertices;
    for (int i = 0; i < 12; ++i) {
        vertices.emplace_back(createNode("Node" + std::to_string(i)));
    }
    std::vector<std::shared_ptr<Edge>> edges;
    edges.emplace_back(createEdge(vertices[0], vertices[5], "a"));
    edges.emplace_back(createEdge(vertices[1], vertices[4], "b"));
    edges.emplace_back(createEdge(vertices[4], vertices[5], "c"));
    edges.emplace_back(createEdge(vertices[2], vertices[4], "d"));
    edges.emplace_back(createEdge(vertices[3], vertices[7], "e"));
    edges.emplace_back(createEdge(vertices[6], vertices[7], "f"));
    edges.emplace_back(createEdge(vertices[7], vertices[11], "g"));
    edges.emplace_back(createEdge(vertices[6], vertices[8], "h"));
    edges.emplace_back(createEdge(vertices[6], vertices[8], "i"));
    edges.emplace_back(createEdge(vertices[5], vertices[9], "j"));
    edges.emplace_back(createEdge(vertices[8], vertices[9], "k"));
    edges.emplace_back(createEdge(vertices[10], vertices[11], "l"));
    edges.emplace_back(createEdge(vertices[9], vertices[11], "m"));
    edges.emplace_back(createEdge(vertices[10], vertices[10], "n"));

    for (auto& vertex : vertices) {
        BOOST_CHECK(vertex != nullptr);
        BOOST_CHECK(!vertex->getName().empty());
        BOOST_TEST_CHECKPOINT("Vertex: " + vertex->getName());
        for (auto& edge : vertex->getEdges()) {
            BOOST_CHECK(edge != nullptr);
            BOOST_CHECK(!edge->getName().empty());
            BOOST_TEST_CHECKPOINT("Edge: " 
                + edge->getName() + " from " + vertex->getName()
                + " to " 
                + std::dynamic_pointer_cast<Edge>(edge)->getOtherVertex(vertex)->getName());
        }
    }
}
