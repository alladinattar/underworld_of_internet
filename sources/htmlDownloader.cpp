#include "htmlDownloader.hpp"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include "gumbo.h"
#include "iostream"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

std::vector<std::string> htmlDownloader::downloadPages(std::vector<std::string> URLs) {
  std::vector<std::string> htmlPages;
  stopPoint_+=1;
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
  if (depth_==stopPoint_){

  }
  return htmlPages;
}









