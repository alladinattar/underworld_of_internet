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
      /*


      ("output",po::value<std::string>(),"path to output file")*/
      ;
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  /*


    htmlDownloader downloader = htmlDownloader(vm["url"].as<std::string>());
    std::string result = downloader.downloadPage(vm["url"].as<std::string>());
    htmlParser parser = htmlParser(1, "");
    parser.collectLinks(result);
    //std::cout<< result<<std::endl;*/

  ThreadPool parserPool(vm["parser_threads"].as<int>());
  ThreadPool downloaderPool(vm["network_threads"].as<int>());

  //int stopPoint = 0;

  if (vm["depth"].as<int>() == 0 ){

  }
  htmlDownloader startDownloader =
      htmlDownloader(parserPool, vm["depth"].as<int>());

  std::vector<std::string> urls = {vm["url"].as<std::string>()};

  htmlParser parser = htmlParser(downloaderPool);
  std::vector<std::string> pages =
      startDownloader.startDownloadPages({vm["url"].as<std::string>()});

  std::vector<std::string> links = parser.collectLinks(pages);
  for (auto k : links) {
    std::cout << k;
  }
  /*downloaderPool.enqueue([&](void) {
    htmlDownloader downloader =
        htmlDownloader(parserPool, vm["depth"].as<int>(), stopPoint);
    std::vector<std::string> pages =
        downloader.downloadPages({vm["url"].as<std::string>()}, parserPool  );
    parserPool.enqueue([&](void) {
      htmlParser parser = htmlParser(downloaderPool);
      std::vector<std::string> links = parser.collectLinks(pages);
      for (auto k : links) {
        std::cout << k;
      }
    });
  });*/

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }
}