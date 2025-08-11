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

// Helper: parse and unparse graph, then compare output to input (optionally
// sorted)
void check_graph_parse_unparse(const std::string &infile,
                               const std::string &outfile,
                               bool sort_compare = false) {
  auto graph = createGraph(infile);
  graph->parse();
  std::string outstring = graph->unparse();
  write_to_file(outfile, outstring);

  if (sort_compare) {
    std::string sorted_infile = outfile + "_sorted_in.txt";
    std::string sorted_outfile = outfile + "_sorted_out.txt";
    BOOST_REQUIRE(sort_file(infile, sorted_infile));
    BOOST_REQUIRE(sort_file(outfile, sorted_outfile));
    BOOST_REQUIRE(files_are_equal(sorted_infile, sorted_outfile));
  } else {
    BOOST_REQUIRE(files_are_equal(infile, outfile));
  }
}

BOOST_AUTO_TEST_CASE(test01_ingest_input) {
  std::string infile_path("/home/vohm/dev/libnae/tests/twist.nae");
  auto graph = createGraph(infile_path);
  BOOST_REQUIRE(graph->fileToString());
  auto data = graph->getInputString();
  std::string outfile_path = "/tmp/test01_output.txt";
  write_to_file(outfile_path, data);
  BOOST_REQUIRE(files_are_equal(infile_path, outfile_path));
}

BOOST_AUTO_TEST_CASE(test02_basic_parse) {
  check_graph_parse_unparse("/home/vohm/dev/libnae/tests/twist.nae",
                            "/tmp/test02_output.txt", true);
}

BOOST_AUTO_TEST_CASE(test03_shortest_path) {
  check_graph_parse_unparse("/home/vohm/dev/libnae/tests/twist.nae",
                            "/tmp/test03_output.txt", true);
  auto graph = createGraph("/home/vohm/dev/libnae/tests/twist.nae");
  graph->parse();
  auto v1 = graph->findVertex("n00");
  auto v2 = graph->findVertex("n03");
  BOOST_REQUIRE(v1 != nullptr);
  BOOST_REQUIRE(v2 != nullptr);
  BOOST_REQUIRE(Algorithms::findShortestPath(graph, v1, v2));
}
