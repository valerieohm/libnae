#define BOOST_TEST_MODULE LibNaeTest
#include <algorithms.hpp>
#include <edge.hpp>
#include <graph.hpp>
#include <vertex.hpp>

#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include <memory>

using namespace nae;

// Logging config for Boost.Test
struct LogConfig {
  LogConfig() {
    boost::unit_test::unit_test_log.set_stream(std::cout);
    boost::unit_test::unit_test_log.set_threshold_level(
        boost::unit_test::log_messages);
  }
} logConfig;

// Helper: write string to file
void write_to_file(const std::string &path, const std::string &data) {
  std::ofstream outfile(path, std::ios::out);
  outfile << data;
  outfile.close();
}

// Helper: sort file and write to another file
bool sort_file(const std::string &in, const std::string &out) {
  std::string cmd = "sort " + in + " > " + out;
  return system(cmd.c_str()) == 0;
}

// Helper: diff two files
bool files_are_equal(const std::string &f1, const std::string &f2) {
  std::string cmd = "diff " + f1 + " " + f2;
  return system(cmd.c_str()) == 0;
}

BOOST_AUTO_TEST_CASE(test01_ingest_input) {
    std::string infile_path("/home/vohm/dev/libnae/tests/twist.dot");
    auto graph = createGraph(infile_path);
    BOOST_REQUIRE(graph->fileToString());
    auto data = graph->getInputString();
    std::string outfile_path = "/tmp/test01_output.txt";
    write_to_file(outfile_path, data);
    BOOST_REQUIRE(files_are_equal(infile_path, outfile_path));
}

BOOST_AUTO_TEST_CASE(test02_basic_parse) {
    auto graph = createGraph("/home/vohm/dev/libnae/tests/twist.dot");
    BOOST_REQUIRE(graph->parse());
    BOOST_REQUIRE_EQUAL(graph->getVertexCount(), 12);
    BOOST_REQUIRE_EQUAL(graph->getEdgeCount(), 14);

    // Test that we can generate output
    std::string output = graph->unparse();
    BOOST_REQUIRE(!output.empty());
    BOOST_REQUIRE(output.find("graph G") != std::string::npos);
}

BOOST_AUTO_TEST_CASE(test03_shortest_path) {
    auto graph = createGraph("/home/vohm/dev/libnae/tests/twist.dot");
    BOOST_REQUIRE(graph->parse());
    auto v1 = graph->findVertex("n00");
    auto v2 = graph->findVertex("n03");
    BOOST_REQUIRE(v1 != nullptr);
    BOOST_REQUIRE(v2 != nullptr);
    BOOST_REQUIRE(Algorithms::findShortestPath(graph, v1, v2));
}

BOOST_AUTO_TEST_CASE(test04_dot_roundtrip) {
    // Test DOT roundtrip parsing
    auto graph1 = createGraph("/home/vohm/dev/libnae/tests/twist.dot");
    graph1->parse();

    std::string output1 = graph1->unparse();
    write_to_file("/tmp/test04_intermediate.dot", output1);

    auto graph2 = createGraph("/tmp/test04_intermediate.dot");
    BOOST_REQUIRE(graph2->parse());

    // Verify same structure
    BOOST_REQUIRE_EQUAL(graph1->getVertexCount(), graph2->getVertexCount());
    BOOST_REQUIRE_EQUAL(graph1->getEdgeCount(), graph2->getEdgeCount());
}

BOOST_AUTO_TEST_CASE(test05_position_parsing) {
    auto graph = createGraph("/home/vohm/dev/libnae/tests/twist.dot");
    BOOST_REQUIRE(graph->parse());

    // Check that vertices with positions are parsed correctly
    auto v00 = graph->findVertex("n00");
    auto v05 = graph->findVertex("n05");
    auto v10 = graph->findVertex("n10");

    BOOST_REQUIRE(v00 != nullptr);
    BOOST_REQUIRE(v05 != nullptr);
    BOOST_REQUIRE(v10 != nullptr);

    // Verify positions are stored (without the exclamation mark)
    BOOST_REQUIRE_EQUAL(v00->getUserStringField(), "0,0");
    BOOST_REQUIRE_EQUAL(v05->getUserStringField(), "1,2");
    BOOST_REQUIRE_EQUAL(v10->getUserStringField(), "2,6");
}
