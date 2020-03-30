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

#include "config_elements.h"
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <cstdlib>
#include <vector>

struct config {
    explicit config(const std::string& filename = "config.json");
    explicit config(const boost::property_tree::ptree& json_data);

    config_nodes::server server_;
    config_nodes::databases databases_;
    config_nodes::html html_;
};
