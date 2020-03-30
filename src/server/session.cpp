#include "session.h"

#include "../application/application.h"
#include <functional>

void fail(beast::error_code ec, char const* what)
{
    application::get().logger_.error(std::string(what) + ": " + ec.message());
}
template <typename protocol>
void session_fail(beast::error_code ec, char const* what, const boost::asio::ip::basic_endpoint<protocol>& endpoint)
{
    application::get().logger_.error_event(std::string(what) + ": " + ec.message(), endpoint);
}

session::session(tcp::socket&& socket)
    : stream_(std::move(socket))
    , req_()
{
}

void session::run()
{
    net::dispatch(stream_.get_executor(),
        beast::bind_front_handler(&session::do_read, shared_from_this()));
}

void session::do_read()
{
    stream_.expires_after(std::chrono::seconds(30));
    http::async_read(stream_, buffer_, req_,
        beast::bind_front_handler(&session::on_read, shared_from_this()));
}

void session::on_read(beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec == http::error::end_of_stream) {
        return do_close();
    } else if (ec) {
        return session_fail(ec, "read", stream_.socket().remote_endpoint());
    }

    application::get().redis_database_.get_address(static_cast<std::string>(req_.target()), [x = shared_from_this()](std::string&& res) {
        x->on_handle_db_answer(std::move(res));
    });
}

void session::on_handle_db_answer(std::string&& res)
{
    if (res == "") {
        res_ = application::get().html_templates_.get_not_found(req_.version());
    } else {
        res_ = application::get().html_templates_.get_redirection(res, req_.version());
    }
    application::get().logger_.log_network_event("GET " + req_.target().to_string(), stream_.socket().remote_endpoint());

    http::async_write(stream_, res_,
        beast::bind_front_handler(&session::on_write, shared_from_this(), res_.need_eof()));
}

void session::on_write(bool close, beast::error_code ec, std::size_t bytes_transferred)
{
    boost::ignore_unused(bytes_transferred);

    if (ec) {
        return session_fail(ec, "write", stream_.socket().remote_endpoint());
    }

    if (close) {
        return do_close();
    }

    do_read();
}

void session::do_close()
{
    beast::error_code ec;
    stream_.socket().shutdown(tcp::socket::shutdown_send, ec);
}