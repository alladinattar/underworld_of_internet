// Copyright 2021 Rinat <rinamuka4@gmail.com>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_
#include <boost/beast/http/message.hpp>

#include "iostream"
class htmlDownloader {
 private:
  std::string baseURL_;

 public:
  htmlDownloader(std::string baseURL):baseURL_(baseURL) {};
  std::string downloadPage(std::string URL);
};


#endif // INCLUDE_HEADER_HPP_
