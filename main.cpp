#include <boost/program_options.hpp>

#include "boost/program_options.hpp"
#include "iostream"
namespace po = boost::program_options;

int main(int argc, char* argv[]){
  po::options_description desc("Must have options");
  desc.add_options()
      ("help", "produce help message")
      ("url", po::value<std::string>(), "HTML page address")
      ("depth",po::value<int>(), "page search depth")
      ("network_threads", po::value<int>(), "number of threads to download pages")
      ("parser_threads", po::value<int>(),"number of threads to process pages")
      ("output",po::value<std::string>(),"path to output file")
      ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    return 1;
  }

  if (vm.count("compression")) {
    std::cout << "Compression level was set to "
         << vm["compression"].as<int>() << ".\n";
  } else {
    std::cout << "Compression level was not set.\n";
  }
}