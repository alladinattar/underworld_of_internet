#include "htmlDownloader.hpp"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include "gumbo.h"
#include "htmlParser.hpp"
#include "iostream"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void htmlDownloader::startDownload(std::vector<url> URLs, int depth) {
  downloaderPool_.enqueue(
      [this, URLs, depth]() { this->downloadPages(URLs, depth); });
}

void htmlDownloader::downloadPages(std::vector<url> URLs, int depth) {
  if (depth < 0) {
    return;
  }
  if (URLs.empty()) {
    std::cerr << "Empty URLs" << std::endl;
  }
  std::vector<std::string> htmlPages;
  for (auto& url : URLs) {
    net::io_context ioc;

    tcp::resolver resolver(ioc);
    beast::tcp_stream stream(ioc);
    auto const results = resolver.resolve(url.domen, "80");
    try {
      stream.connect(results);
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
      continue;
    }

    http::request<http::string_body> req{http::verb::get, url.uri, 10};
    req.set(http::field::content_type, "text/plain");
    req.set(http::field::host, "http-client-sync");

    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    http::write(stream, req);
    beast::flat_buffer buffer;
    http::response<http::string_body> res;
    http::read(stream, buffer, res);

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);
    if (ec && ec != beast::errc::not_connected) throw beast::system_error{ec};
    htmlPages.push_back(res.body());
  }

  this->parserObj_.startParse(htmlPages, *this, depth);
}
