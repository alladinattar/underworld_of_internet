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
  void startDownloadPages(std::vector<std::string> URLs, ThreadPool& parserPool,ThreadPool& downloaderPool, ThreadPool& outputPool, std::string path);
};

#endif  // INCLUDE_HEADER_HPP_
