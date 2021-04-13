//Copyright 2021 <rinamuka4@gmail.com>

#ifndef INCLUDE_OUTPUT_HPP_
#define INCLUDE_OUTPUT_HPP_
#include "ThreadPool.h"
#include "fstream"
#include "iostream"
#include "vector"
#include "string"
class outPut {
 private:
  std::string path_;
  ThreadPool pool;
  std::ofstream file;
  void writeFile(std::vector<std::string> imgs);

 public:
  explicit outPut(std::string path) : path_(path), pool(1), file(path) {}
  void writeIMG(std::vector<std::string> imgs);
  ~outPut() { file.close(); }
};

#endif  // INCLUDE_OUTPUT_HPP_
