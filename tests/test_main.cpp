#define BOOST_TEST_MODULE LibNaeTest
#include <edge.h>
#include <vertex.h>
#include <graph.h>

#include <boost/test/included/unit_test.hpp>
#include <memory>

using namespace nae;

struct LogConfig {
  LogConfig() {
    boost::unit_test::unit_test_log.set_stream(std::cout);
    boost::unit_test::unit_test_log.set_threshold_level(
        boost::unit_test::log_messages);
  }
} logConfig;

BOOST_AUTO_TEST_CASE(test01_ingest_input) {

  std::string infile_path("/home/vohm/dev/libnae/tests/twist.nae");
  auto graph = createGraph(infile_path);
  BOOST_REQUIRE(graph->fileToString());
  auto data = graph->getInputString();
  // write data to file
  std::ofstream outfile("/tmp/test01_output.txt",
                        std::ios::out);
  outfile << data;
  outfile.close();
  std::string command("diff /home/vohm/dev/libnae/tests/twist.nae /tmp/test01_output.txt");
  int res = system(command.c_str());
  BOOST_REQUIRE(res == 0); // Check if the files are identical
}

BOOST_AUTO_TEST_CASE(test02_basic_parse) {
  std::string infile_path("/home/vohm/dev/libnae/tests/twist.nae");
  auto graph = createGraph(infile_path);
  graph->parse();
  std::string outstring = graph->unparse();
    std::ofstream outfile("/tmp/test02_output.txt",
                        std::ios::out);
  outfile << outstring;
  outfile.close();
  std::string command("diff /home/vohm/dev/libnae/tests/twist.nae /tmp/test02_output.txt");
  int res = system(command.c_str());
  BOOST_REQUIRE(res == 0); // Check if the files are identical

}

