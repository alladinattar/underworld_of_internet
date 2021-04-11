#include <boost/program_options.hpp>
#include "htmlDownloader.hpp"
#include "htmlParser.hpp"
#include "boost/program_options.hpp"
#include "iostream"
namespace po = boost::program_options;

int main(int argc, char* argv[]){
  po::options_description desc("Must have options");
  desc.add_options()
      ("help", "produce help message")
      ("url", po::value<std::string>(), "HTML page address")
      /*("depth",po::value<int>(), "page search depth")
      ("network_threads", po::value<int>(), "number of threads to download pages")
      ("parser_threads", po::value<int>(),"number of threads to process pages")
      ("output",po::value<std::string>(),"path to output file")*/
      ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }



  htmlDownloader downloader = htmlDownloader(vm["url"].as<std::string>());
  std::string result = downloader.downloadPage(vm["url"].as<std::string>());
  htmlParser parser = htmlParser(1, "");
  parser.parsePage(result);
  //std::cout<< result<<std::endl;
}