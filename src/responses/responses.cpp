#include "responses.hpp"

html_templates::html_templates(std::ifstream&& redirect_html, std::ifstream&& error404_html)
{
    std::stringstream str_stream;
    str_stream << redirect_html.rdbuf();
    redirect_body_ = str_stream.str();

    str_stream.clear();
    str_stream << error404_html.rdbuf();
    error404_body_ = str_stream.str();

    //    std::cout <<
}

html_templates::html_templates(const std::string& redirect_html, const std::string& error404_html)
    : html_templates(std::ifstream(redirect_html), std::ifstream(error404_html))
{
}

http::response<http::string_body> html_templates::get_redirection(std::string redirection_url, int http_version)
{
    http::response<http::string_body> res(http::status::permanent_redirect, http_version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.set(http::field::location, redirection_url);
    res.keep_alive(false);
    res.body() = redirect_body_;
    res.prepare_payload();
    return res;
}

http::response<http::string_body> html_templates::get_not_found(int http_version)
{
    http::response<http::string_body> res(http::status::not_found, http_version);
    res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    res.keep_alive(false);
    res.body() = error404_body_;
    res.prepare_payload();
    return res;
};