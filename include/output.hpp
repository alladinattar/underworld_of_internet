
#ifndef INCLUDE_OUTPUT_HPP_
#define INCLUDE_OUTPUT_HPP_
#include "ThreadPool.h"
#include "fstream"
#include "iostream"
#include "vector"
class outPut {
 private:
  std::string path_;
  ThreadPool pool;
  std::ofstream file;
  void writeFile(std::vector<std::string> imgs);

 public:
  outPut(std::string path) : path_(path), pool(1), file(path) {}
  void writeIMG(std::vector<std::string> imgs);
  ~outPut() { file.close(); }
};

#endif  // INCLUDE_HTML_PARSER_HPP_