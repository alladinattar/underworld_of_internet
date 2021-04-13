// Copyright 2021 Rinat <rinamuka4@gmail.com>

#ifndef INCLUDE_HTMLDOWNLOADER_HPP_
#define INCLUDE_HTMLDOWNLOADER_HPP_
#include <boost/beast/http/message.hpp>
#include "vector"
#include "ThreadPool.h"
#include "htmlParser.hpp"
#include "iostream"
class htmlDownloader {
 private:
  ThreadPool downloaderPool_;
  htmlParser& parserObj_;
  void downloadPages(std::vector<url> URLs, int depth);

 public:
  void startDownload(std::vector<url> URLs, int depth);
  htmlDownloader(htmlParser& parserObj, int threadNum)
      : downloaderPool_(threadNum), parserObj_(parserObj) {}
};

#endif  // INCLUDE_HTMLDOWNLOADER_HPP_
