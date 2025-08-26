#include <graph.hpp>
#include <vertex.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

namespace nae {

namespace {
std::vector<std::string> tokenize(std::string const &line) {
    std::vector<std::string> tokens;
    std::string buffer;
    std::stringstream check1(line);
    while (getline(check1, buffer, ' '))
        tokens.push_back(buffer);
    return tokens;
}
} // namespace

Graph::Parser::Parser(std::string const& infile) : infile_path(infile) {}
bool Graph::Parser::parse(std::shared_ptr<Graph> graph) {
  if (input_string.empty() && !fileToString())
    throw std::runtime_error("Graph::Parser::parse() no string");

  std::istringstream iss(input_string);
  std::string line;

  std::getline(iss, line);
  if (line != "#NAE_0.1")
    throw std::runtime_error("Graph::Parser::parse() invalid header");
  std::getline(iss, line);
  if (line != "#VERTICIES")
    throw std::runtime_error("Graph::Parser::parse() invalid VERTICIES");
  while (std::getline(iss, line)) {
    if (!line.starts_with('#')){
      auto tokens = tokenize(line);
      if (tokens.size() != 2) throw std::runtime_error("vertex line wrong number of tokens");
      graph->addVertex(tokens[0], stoi(tokens[1]));
    }else
      break;
  }
  if (line != "#EDGES")
    throw std::runtime_error("Graph::Parser::parse() invalid EDGES");
  while (std::getline(iss, line)) {
    std::cout << "Line: |" << line << "|" << std::endl;
    auto tokens = tokenize(line);
    if (tokens.size() != 5)
      throw std::runtime_error("Graph::Parser::parse() wrong tokens");
    // make an edge here
    graph->addEdge(tokens[1], tokens[3], tokens[0], stoi(tokens[4]));
  }
  return true;
}

bool Graph::Parser::fileToString() {
  // open file at infile_path and read the contents into input_string
  std::ifstream infile(infile_path.c_str());
  if (!infile) {
    return false;
  }
  std::stringstream buffer;
  buffer << infile.rdbuf();
  input_string = buffer.str();
  return true;
}

std::string const& Graph::Parser::getInputString() {
  if (input_string.empty() && !fileToString())
    throw std::runtime_error("Graph::Parser::getInputString() failed");
  return input_string;
}

} // namespace nae