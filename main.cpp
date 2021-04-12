#include <boost/program_options.hpp>

#include "ThreadPool.h"
#include "boost/program_options.hpp"
#include "htmlDownloader.hpp"
#include "htmlParser.hpp"
#include "iostream"
namespace po = boost::program_options;

int main(int argc, char* argv[]) {
  po::options_description desc("Must have options");
  desc.add_options()
      ("help", "produce help message")
      ("url", po::value<std::string>(), "HTML page address")
      ("network_threads", po::value<int>(), "number of threads to download pages")
      ("parser_threads", po::value<int>(),"number of threads to process pages")
      ("depth",po::value<int>(), "page search depth")
      ("output",po::value<std::string>(),"path to output file")
      ;
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);


  ThreadPool downloadPool(1);
  ThreadPool parserPool(1);
  ThreadPool outputPool(1);

  htmlDownloader downloader = htmlDownloader();
  downloader.startDownloadPages({vm["url"].as<std::string>()}, parserPool, downloadPool, outputPool, vm["output"].as<std::string>());


  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }
}