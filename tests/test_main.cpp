#include <cassert>
#include <iostream>
#include <node.h>

using namespace nae;
int main() {
    std::cout << "Running tests..." << std::endl;
    std::shared_ptr<Node> one = createNode("Node1");
    printf("Created node: %s\n", one->getName().c_str());

    assert(1 + 1 == 2);
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
