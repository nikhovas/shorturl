#pragma once

#include "bredis.hpp"
#include <boost/asio.hpp>
#include <optional>

namespace r = bredis;
namespace asio = boost::asio;
namespace sys = boost::system;

using socket_t = asio::ip::tcp::socket;
using Buffer = boost::asio::streambuf;
using Iterator = typename r::to_iterator<Buffer>::iterator_t;
using Policy = r::parsing_policy::keep_result;
using result_t = r::parse_result_mapper_t<Iterator, Policy>;

class redis_connection : public std::enable_shared_from_this<redis_connection> {
public:
    explicit redis_connection(boost::asio::ip::tcp::socket&& socket_);
    void value_by_key(const std::string& key, const std::function<void(std::string&& res)>& callback);

private:
    bredis::Connection<socket_t> connection_;
    Buffer tx_buff;
    Buffer rx_buff;
};

class redis_database {
public:
    redis_database(boost::asio::io_context& ioc_, const boost::asio::ip::tcp::endpoint& endpoint_);
    void get_address(const std::string& key, std::function<void(std::string&& res)>&& callback);
    std::shared_ptr<redis_connection> new_connection();

private:
    boost::asio::io_context& ioc_;
    boost::asio::ip::tcp::endpoint endpoint_;
};