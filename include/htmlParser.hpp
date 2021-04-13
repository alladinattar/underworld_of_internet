#ifndef INCLUDE_HTML_PARSER_HPP_
#define INCLUDE_HTML_PARSER_HPP_
#include "ThreadPool.h"
#include "output.hpp"
#include "iostream"

class htmlDownloader;
struct url{
  std::string domen;
  std::string uri;
};
class htmlParser {
 private:
  ThreadPool parserPool_;
  outPut& outputObj_;
  void collectIMG(std::vector<std::string> pages, htmlDownloader& downloader, int depth);

 public:
  htmlParser(outPut& outputObj, int threadNum): parserPool_(threadNum),outputObj_(outputObj){}
  void startParse(std::vector<std::string> pages, htmlDownloader& downloader, int depth);


  /*static std::vector<std::string> collectLinks(std::vector<std::string> pages);
  void startParse(std::vector<std::string>& pages, ThreadPool& downloaderPool, ThreadPool& parserPool, ThreadPool& outputPool, std::string path);*/

};
#endif  // INCLUDE_HTML_PARSER_HPP_