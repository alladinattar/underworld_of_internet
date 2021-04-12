#ifndef INCLUDE_HTML_PARSER_HPP_
#define INCLUDE_HTML_PARSER_HPP_
#include "ThreadPool.h"
#include "iostream"
class htmlParser {
 private:
  std::string outputFile_;
  std::vector<std::string> links;
  ThreadPool& downloaderPool;

 public:
  htmlParser(ThreadPool& link) : downloaderPool(link){};
  static std::vector<std::string> collectIMG(std::vector<std::string> pages);
  static std::vector<std::string> collectLinks(std::vector<std::string> pages);
};
#endif  // INCLUDE_HTML_PARSER_HPP_