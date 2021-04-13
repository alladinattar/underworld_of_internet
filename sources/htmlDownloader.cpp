#include "htmlDownloader.hpp"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "gumbo.h"
#include "iostream"
#include "htmlParser.hpp"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

/*std::vector<std::string> htmlDownloader::startDownloadPages(std::vector<std::string> URLs, ThreadPool& parserPool,ThreadPool& downloaderPool, ThreadPool& outputPool, std::string path) {
  std::vector<std::string> htmlPages;
  for (auto & url : URLs){
    net::io_context ioc;

    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve(url, "80");

    stream.connect(results);
    //int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;
    http::request<http::string_body> req{http::verb::get, "/", 10};
    req.set(http::field::content_type, "text/plain");
    req.set(http::field::host, "http-client-sync");

    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(stream, req);
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);

    //std::cout << res << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec};
    htmlPages.push_back(res.body());
  }

  return htmlPages;
}*/







/*
void htmlDownloader::startDownloadPages(std::vector<std::string> URLs, ThreadPool& parserPool, ThreadPool& downloaderPool,ThreadPool& outputPool, std::string path) {
  std::vector<std::string> htmlPages;
  for (auto & url : URLs){
    net::io_context ioc;

    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve(url, "80");

    stream.connect(results);
    http::request<http::string_body> req{http::verb::get, "/", 10};
    req.set(http::field::content_type, "text/plain");
    req.set(http::field::host, "http-client-sync");

    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(stream, req);
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);

    //std::cout << res << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec};
    htmlPages.push_back(res.body());
  }

  parserPool.enqueue([&](void){
    htmlParser parser = htmlParser();
    parser.startParse(htmlPages, downloaderPool,parserPool, outputPool, path);
  });
}*/






void htmlDownloader::downloadPages(std::vector<url> URLs, int depth){
  std::cout<<"depth = "<<depth<<std::endl;
  if (depth<0){return;}
  std::cout<<"hello 1"<<std::endl;
  std::vector<std::string> htmlPages;
  for (auto & url : URLs) {
    net::io_context ioc;

    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);
    //std::cout<<url.uri<<" "<<url.domen<<std::endl;
    auto const results = resolver.resolve(url.domen, "80");
    std::cout<<"hello 1.5"<<std::endl;
    std::cout<<url.domen<<url.uri<<std::endl;
    try{
      stream.connect(results);
    }catch (std::exception& e){
      std::cerr<<e.what()<<std::endl;
      continue;
    }

    std::cout<<"hello 2"<<std::endl;

    http::request<http::string_body> req{http::verb::get, url.uri, 10};
    req.set(http::field::content_type, "text/plain");
    req.set(http::field::host, "http-client-sync");

    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(stream, req);
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);
    std::cout<<"hello 3"<<std::endl;

    // std::cout << res << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec} ;
    htmlPages.push_back(res.body());
  }
  std::cout<<"hello 4"<<std::endl;

  this->parserObj_.collectIMG(htmlPages,*this,depth);
}

