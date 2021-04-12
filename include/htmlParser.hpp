#ifndef INCLUDE_HTML_PARSER_HPP_
#define INCLUDE_HTML_PARSER_HPP_
#include "ThreadPool.h"
#include "iostream"
class htmlParser {
 private:
  std::string outputFile_;

 public:
  static std::vector<std::string> collectIMG(std::vector<std::string> pages);
  static std::vector<std::string> collectLinks(std::vector<std::string> pages);
  void startParse(std::vector<std::string> pages, ThreadPool& downloaderPool, ThreadPool& parserPool, ThreadPool& outputPool, std::string path);

};
#endif  // INCLUDE_HTML_PARSER_HPP_