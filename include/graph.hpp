#ifndef GRAPH_H
#define GRAPH_H
#include <edge.hpp>
#include <vertex.hpp>

#include <memory>
#include <unordered_map>
#include <functional>

namespace nae {

class Graph : public std::enable_shared_from_this<Graph> {
public:
    class Parser {
    public:
        ~Parser() = default;
        explicit Parser(std::string const &infile);

    private:
        Parser() = delete;
        bool parse(std::shared_ptr<Graph> graph);
        friend Graph;
        bool fileToString();
        std::string const &getInputString();
        std::string infile_path;
        std::string input_string;
    };

    Graph(std::string const &infile_name) : parser(infile_name) {}
    bool parse();
    std::string unparse();
    std::string const &getInputString() { return parser.getInputString(); }
    bool fileToString() { return parser.fileToString(); }
    size_t getVertexCount() const { return vmap_.size(); }
    size_t getEdgeCount() const { return emap_.size(); }

    // Iterator support for vertices
    using VertexIterator =
        std::unordered_map<std::string,
                           std::shared_ptr<Vertex>>::const_iterator;
    VertexIterator vertexBegin() const { return vmap_.cbegin(); }
    VertexIterator vertexEnd() const { return vmap_.cend(); }

    // Iterator support for edges
    using EdgeIterator =
        std::unordered_map<std::string, std::shared_ptr<Edge>>::const_iterator;
    EdgeIterator edgeBegin() const { return emap_.cbegin(); }
    EdgeIterator edgeEnd() const { return emap_.cend(); }

    // Apply function to all vertices
    template<typename Func>
    void forEachVertex(Func func) {
        for (auto& pair : vmap_) {
            func(pair.second);
        }
    }

    // Apply function to all edges
    template<typename Func>
    void forEachEdge(Func func) {
        for (auto& pair : emap_) {
            func(pair.second);
        }
    }
private:
    Parser parser;
    std::shared_ptr<Vertex> addVertex(std::string const &name, int cost);
    std::shared_ptr<Edge> addEdge(std::string const &src,
                                  std::string const &dst,
                                  std::string const &name, int cost);
    std::shared_ptr<Edge> findEdge(std::string const &name);

public:
    std::shared_ptr<Vertex> findVertex(std::string const &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Vertex>> vmap_;
    std::unordered_map<std::string, std::shared_ptr<Edge>> emap_;
};
std::shared_ptr<Graph> createGraph(std::string const &infile_name);
} // namespace nae
#endif