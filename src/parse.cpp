#include <graph.hpp>
#include <vertex.hpp>

#include <fstream>
#include <iostream>
#include <sstream>

namespace nae {

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
    if (!line.starts_with('#'))
      graph->addVertex(line);
    else
      break;
  }
  if (line != "#EDGES")
    throw std::runtime_error("Graph::Parser::parse() invalid EDGES");
  while (std::getline(iss, line)) {
    std::cout << "Line: |" << line << "|" << std::endl;
    std::string buffer;
    std::vector<std::string> tokens;
    std::stringstream check1(line);
    while (getline(check1, buffer, ' ')) tokens.push_back(buffer);
    if (tokens.size() != 4)
      throw std::runtime_error("Graph::Parser::parse() wrong tokens");
    // make an edge here
    graph->addEdge(tokens[1], tokens[3], tokens[0]);
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

}  // namespace nae