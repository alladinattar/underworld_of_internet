// Copyright 2021 Rinat <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/beast/http/message.hpp>

#include "ThreadPool.h"
#include "htmlParser.hpp"
#include "iostream"
class htmlDownloader {
 private:
  ThreadPool downloaderPool_;
  htmlParser& parserObj_;

 public:
  htmlDownloader(htmlParser& parserObj, int threadNum)
      : downloaderPool_(threadNum),parserObj_(parserObj) {}
  void downloadPages(std::vector<url> URLs, int depth);
};

#endif  // INCLUDE_HEADER_HPP_
