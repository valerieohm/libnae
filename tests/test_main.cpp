#define BOOST_TEST_MODULE LibNaeTest
#include <boost/test/included/unit_test.hpp>
#include <node.h>

using namespace nae;

BOOST_AUTO_TEST_CASE(node_creation)
{
    std::shared_ptr<Node> one = createNode("Node1");
    BOOST_TEST(one != nullptr);
    // Uncomment if getName() is implemented:
    // BOOST_TEST(one->getName() == "Node1");
}
