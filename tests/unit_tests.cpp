#include "gtest/gtest.h"
#include "bredis/Connection.hpp"
#include "bredis/MarkerHelpers.hpp"
#include <boost/asio.hpp>
#include <bredis/Extract.hpp>

using Iterator = typename bredis::to_iterator<boost::asio::streambuf>::iterator_t;
using result_t = bredis::parse_result_mapper_t<Iterator, bredis::parsing_policy::keep_result>;

TEST(Prepairing, RedisConnection)
{
    boost::asio::io_context io_service;
    boost::asio::ip::tcp::endpoint end_point(boost::asio::ip::address::from_string(REDIS_IP), REDIS_PORT);
    boost::asio::ip::tcp::socket socket(io_service, end_point.protocol());
    boost::asio::streambuf tx_buff, rx_buff;
    ASSERT_NO_THROW(socket.connect(end_point));

    bredis::Connection<boost::asio::ip::tcp::socket> c(std::move(socket));
    c.async_write(tx_buff, bredis::single_command_t{"llen", "my-queue"}, [&](const boost::system::error_code &ec, std::size_t bytes_transferred) {
        ASSERT_EQ(ec.value(), 0);
        tx_buff.consume(bytes_transferred);
        c.async_read(rx_buff, [&](const boost::system::error_code &ec, result_t &&r) {
            auto extract = boost::apply_visitor(bredis::extractor<Iterator>(), r.result);
            ASSERT_EQ(boost::get<bredis::extracts::int_t>(extract), 0);
            rx_buff.consume(r.consumed);
        });
    });
}
