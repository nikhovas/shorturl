#include "redis_database.h"

redis_connection::redis_connection(boost::asio::ip::tcp::socket&& socket_) : connection_(std::move(socket_)) {}

void redis_connection::value_by_key(const std::string& key, const std::function<void(std::string&& res)>& callback) {
    auto this_ = shared_from_this();
    connection_.async_write(tx_buff, r::single_command_t{"get", key},
            [this_, callback](const sys::error_code &ec, std::size_t bytes_transferred) {
        this_->tx_buff.consume(bytes_transferred);
        this_->connection_.async_read(this_->rx_buff, [this_, callback](const sys::error_code &ec, result_t &&r) {
            if (ec) {
                std::cout << ec.message() << std::endl;
            }
            auto extract = boost::apply_visitor(r::extractor<Iterator>(), r.result);
            std::string result;
            try {
                result = boost::get<r::extracts::string_t>(extract).str;
            } catch (...) {}
            this_->rx_buff.consume(r.consumed);
            callback(std::move(result));
        });
    });
}



redis_database::redis_database(boost::asio::io_context& ioc_, const boost::asio::ip::tcp::endpoint& endpoint_) :
ioc_(ioc_), endpoint_(endpoint_){}

void redis_database::get_address(const std::string& key, std::function<void(std::string&& res)>&& callback) {
    auto conn = new_connection();
    auto x = conn->shared_from_this();
    conn->value_by_key(key, callback);
}

std::shared_ptr<redis_connection> redis_database::new_connection() {
    socket_t socket_(ioc_, endpoint_.protocol());
    socket_.connect(endpoint_);
    return std::make_shared<redis_connection>(std::move(socket_));
}