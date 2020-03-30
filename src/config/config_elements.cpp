#include "config_elements.h"

namespace config_nodes {
server::server(const boost::property_tree::ptree& json_data)
    : address_(boost::asio::ip::make_address(json_data.get<std::string>("address")))
    , port_(json_data.get<std::size_t>("port"))
    , threads_(json_data.get<std::size_t>("threads"))
{
}

database_node::database_node(const boost::property_tree::ptree& json_data)
    : address_(boost::asio::ip::make_address(json_data.get<std::string>("address")))
    , port_(json_data.get<std::size_t>("port"))
{
}

databases::databases(const boost::property_tree::ptree& json_data)
{
    for (auto it = json_data.begin(); it != json_data.end(); ++it) {
        databases_.emplace_back(it->second);
    }
}

html::html(const boost::property_tree::ptree& json_data)
    : error404_(json_data.get<std::string>("error404"))
    , redirect_(json_data.get<std::string>("redirect"))
{
}
}
