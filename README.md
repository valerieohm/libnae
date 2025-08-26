# LibNAE - Graph Library

A C++ graph library supporting the Graphviz DOT format and graph algorithms.

## Features

- **DOT Format Support**: Full Graphviz DOT format parsing and generation
- **Graph Operations**: Vertex and edge manipulation
- **Algorithms**: Shortest path finding (Dijkstra's algorithm)
- **Modern C++**: Uses smart pointers and RAII principles

## Supported Format

### DOT Format (Graphviz)
```
digraph G {
    vertex_name [cost=value]
    src_vertex -> dst_vertex [label="edge_name", cost=value]
}
```

## Building

This project uses Bazel for building:

```bash
# Build the library
bazel build //:libnae

# Build and run tests
bazel test //tests:test_main
```

## Usage

### Basic Graph Operations

```cpp
#include <graph.hpp>

// Create and parse a graph
auto graph = nae::createGraph("input.dot");
graph->parse();

// Access graph information
std::cout << "Vertices: " << graph->getVertexCount() << std::endl;
std::cout << "Edges: " << graph->getEdgeCount() << std::endl;

// Find vertices
auto vertex = graph->findVertex("vertex_name");

// Output DOT format
std::string dot_output = graph->unparse();
```

### Algorithms

```cpp
#include <algorithms.hpp>

// Find shortest path between vertices
auto start = graph->findVertex("start");
auto end = graph->findVertex("end");
bool found = nae::Algorithms::findShortestPath(graph, start, end);
```

## DOT Format Attributes

- **Vertices**: `cost` attribute specifies the vertex cost
- **Edges**: `label` attribute specifies the edge name, `cost` attribute specifies the edge cost

## Visualization

DOT files can be visualized using Graphviz tools:

```bash
# Generate PNG
dot -Tpng input.dot -o output.png

# Generate SVG
dot -Tsvg input.dot -o output.svg
```

## License

See [LICENSE](LICENSE) file for details.
