#include "iostream"
class htmlParser{
 private:
  int parser_threads_;
  std::string outputFile_;
 public:
  htmlParser(size_t thrds, std::string outputFile):parser_threads_(thrds), outputFile_(outputFile){};
  static void parsePage(std::string page);
};