#define BOOST_TEST_MODULE LibNaeTest
#include <edge.hpp>
#include <vertex.hpp>
#include <graph.hpp>

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
  std::string sorted_infile = "/tmp/test02_sorted_in.txt";
  std::string sorted_outfile = "/tmp/test02_sorted_out.txt";
  std::string sort_in_cmd =
      "sort /home/vohm/dev/libnae/tests/twist.nae > " + sorted_infile;
  std::string sort_out_cmd = "sort /tmp/test02_output.txt > " + sorted_outfile;
  int res1 = system(sort_in_cmd.c_str());
  int res2 = system(sort_out_cmd.c_str());
  BOOST_REQUIRE(res1 == 0);
  BOOST_REQUIRE(res2 == 0);
  std::string command("diff " + sorted_infile + " " + sorted_outfile);
  int res = system(command.c_str());
  BOOST_REQUIRE(res == 0); // Check if the sorted files are identical
}

