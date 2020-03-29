#include "config.h"

#include "../boost_addons/property_tree.h"

config::config(const boost::property_tree::ptree& json_data)
:
server_(config_nodes::server(json_data.get_child("server"))),
databases_(config_nodes::databases(json_data.get_child("databases"))),
html_(config_nodes::html(json_data.get_child("html")))
{}

config::config(const std::string& filename) : config(boost::property_tree::from_json_file(filename)) {}