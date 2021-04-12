
#ifndef INCLUDE_OUTPUT_HPP_
#define INCLUDE_OUTPUT_HPP_
#include "iostream"
#include "vector"
#include "ThreadPool.h"
class outPut{
 private:
  std::string path_;
  ThreadPool pool;
  void writeFile(std::vector<std::string> imgs);
 public:
  outPut(std::string path): path_(path), pool(1){}
  void writeIMG(std::vector<std::string> imgs);
};

#endif  // INCLUDE_HTML_PARSER_HPP_