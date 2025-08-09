#ifndef GRAPH_H
#define GRAPH_H
#include <edge.h>
#include <vertex.h>

#include <memory>
#include <unordered_map>

namespace nae {

template<typename Key, typename T>
class OrderedMap {
public:
    void insert(const Key& key, const T& value) {
        if (map_.find(key) == map_.end()) {
            order_.push_back(key);
        }
        map_[key] = value;
    }

    T& operator[](const Key& key) { return map_[key]; }
    typename std::unordered_map<Key, T>::iterator find(const Key& key) { return map_.find(key); }
    typename std::unordered_map<Key, T>::iterator end() { return map_.end(); }

    // Iterate in insertion order
    auto begin() { return order_.begin(); }
    auto endOrder() { return order_.end(); }
    T& atOrder(size_t idx) { return map_[order_[idx]]; }
    size_t size() const { return order_.size(); }

private:
    std::unordered_map<Key, T> map_;
    std::vector<Key> order_;
};


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
    std::string const & getInputString();
    std::string infile_path;
    std::string input_string;
  };

  Graph(std::string const &infile_name) : parser(infile_name) {}
  bool parse();
  std::string unparse();
  std::string const& getInputString() { return parser.getInputString();}
  bool fileToString() {
    return parser.fileToString();
  }


 private:
  Parser parser;
  std::shared_ptr<Vertex> addVertex(std::string const &name);
  std::shared_ptr<Edge> addEdge(std::string const &src, std::string const &dst,
                                std::string const &name);
  std::shared_ptr<Vertex> findVertex(std::string const &name);
  std::shared_ptr<Edge> findEdge(std::string const &name);

 private:
  OrderedMap<std::string, std::shared_ptr<Vertex>> vmap_;
  OrderedMap<std::string, std::shared_ptr<Edge>> emap_;
};
std::shared_ptr<Graph> createGraph(std::string const &infile_name);
}  // namespace nae
#endif