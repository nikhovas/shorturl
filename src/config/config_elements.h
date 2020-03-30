#pragma once

#pragma once

#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <cstdlib>
#include <string>
#include <vector>

#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <cstdlib>
#include <vector>

namespace config_nodes {
struct config_element {
};

struct server : public config_element {
public:
    server() = default;

    explicit server(const boost::property_tree::ptree& json_data);

    //    private:
    boost::asio::ip::address address_;
    std::size_t port_;
    std::size_t threads_;
};

struct database_node : public config_element {
public:
    database_node() = default;

    explicit database_node(const boost::property_tree::ptree& json_data);

    boost::asio::ip::address address_;
    std::size_t port_;
};

struct databases : public config_element {
public:
    databases() = default;

    explicit databases(const boost::property_tree::ptree& json_data);

    std::vector<database_node> databases_;
};

struct html : public config_element {
    html() = default;

    explicit html(const boost::property_tree::ptree& json_data);

    std::string error404_;
    std::string redirect_;
};
}