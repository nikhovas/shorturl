#pragma once

#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/config.hpp>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

//#include "../application/application.h"

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http; // from <boost/beast/http.hpp>
namespace net = boost::asio; // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>

class html_templates {
public:
    html_templates(std::ifstream&& redirect_html, std::ifstream&& error404_html);
    html_templates(const std::string& redirect_html, const std::string& error404_html);

    http::response<http::string_body> get_redirection(std::string redirection_url, int http_version);
    http::response<http::string_body> get_not_found(int http_version);

private:
    std::string redirect_body_;
    std::string error404_body_;
};