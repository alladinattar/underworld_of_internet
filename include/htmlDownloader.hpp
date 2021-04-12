// Copyright 2021 Rinat <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/beast/http/message.hpp>

#include "ThreadPool.h"
#include "htmlParser.hpp"
#include "iostream"
class htmlDownloader {
 private:

 public:
  std::vector<std::string> startDownloadPages(std::vector<std::string> URLs);
  void downloadPages(std::vector<std::string> URLs, ThreadPool& parserPool,ThreadPool& downloaderPool);
};

#endif  // INCLUDE_HEADER_HPP_
