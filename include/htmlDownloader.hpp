// Copyright 2021 Rinat <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/beast/http/message.hpp>

#include "ThreadPool.h"
#include "htmlParser.hpp"
#include "iostream"
class htmlDownloader {
 private:
  std::vector<std::string> links;
  ThreadPool& parserPool;
  int depth_;
 public:
  htmlDownloader(ThreadPool& link, int depth/*, int stopPoint*/):parserPool(link), depth_(depth){};
  std::vector<std::string> startDownloadPages(std::vector<std::string> URLs);
  std::vector<std::string> downloadPages(std::vector<std::string> URLs, int& stopPoint);
};

#endif  // INCLUDE_HEADER_HPP_
