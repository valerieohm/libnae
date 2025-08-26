#include <graph.hpp>
#include <vertex.hpp>

#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>

namespace nae {

namespace {} // namespace

Graph::Parser::Parser(std::string const& infile) : infile_path(infile) {}

bool Graph::Parser::parse(std::shared_ptr<Graph> graph) {
  if (input_string.empty() && !fileToString())
    throw std::runtime_error("Graph::Parser::parse() no string");

  std::istringstream iss(input_string);
  return parseDOT(graph, iss);
}

bool Graph::Parser::parseDOT(std::shared_ptr<Graph> graph,
                             std::istringstream &iss) {
    std::string line;
    std::string content;

    // Read entire content and remove comments
    while (std::getline(iss, line)) {
        size_t commentPos = line.find("//");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }
        content += line + "\n";
    }

    // Parse vertices with attributes
    std::regex nodePattern(R"((\w+)\s*\[([^\]]*)\])");
    std::sregex_iterator nodeIter(content.begin(), content.end(), nodePattern);
    std::sregex_iterator nodeEnd;

    for (; nodeIter != nodeEnd; ++nodeIter) {
        std::string nodeName = (*nodeIter)[1];
        std::string attributes = (*nodeIter)[2];

        int cost = 1;         // default cost
        std::string pos = ""; // position attribute

        // Extract cost
        std::regex costPattern(R"(cost\s*=\s*(\d+))");
        std::smatch costMatch;
        if (std::regex_search(attributes, costMatch, costPattern)) {
            cost = std::stoi(costMatch[1]);
        }

        // Extract pos attribute
        std::regex posPattern("pos\\s*=\\s*\"([^\"!]*)!?\"");
        std::smatch posMatch;
        if (std::regex_search(attributes, posMatch, posPattern)) {
            pos = posMatch[1];
        }

        auto vertex = graph->addVertex(nodeName, cost);

        // Store position if found
        if (!pos.empty()) {
            // Use the user string field to store position
            vertex->setUserStringField(pos);
        }
    }

    // Parse edges with attributes
    std::regex edgePattern(R"((\w+)\s*--\s*(\w+)\s*(?:\[([^\]]*)\])?)");
    std::sregex_iterator edgeIter(content.begin(), content.end(), edgePattern);
    std::sregex_iterator edgeEnd;

    for (; edgeIter != edgeEnd; ++edgeIter) {
        std::string srcName = (*edgeIter)[1];
        std::string dstName = (*edgeIter)[2];
        std::string attributes = (*edgeIter)[3];

        std::string label = srcName + "_" + dstName;
        int cost = 1; // default cost

        if (!attributes.empty()) {
            // Extract label
            std::regex labelPattern("label\\s*=\\s*\"([^\"]*)\"");
            std::smatch labelMatch;
            if (std::regex_search(attributes, labelMatch, labelPattern)) {
                label = labelMatch[1];
            }

            // Extract cost
            std::regex costPattern(R"(cost\s*=\s*(\d+))");
            std::smatch costMatch;
            if (std::regex_search(attributes, costMatch, costPattern)) {
                cost = std::stoi(costMatch[1]);
            }
        }

        graph->addEdge(srcName, dstName, label, cost);
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