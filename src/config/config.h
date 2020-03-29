#pragma once

#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

#include <string>
#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <vector>

#include <boost/beast/core.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <vector>
#include "config_elements.h"

struct config {
    explicit config(const std::string& filename = "config.json");
    explicit config(const boost::property_tree::ptree& json_data);

    config_nodes::server server_;
    config_nodes::databases databases_;
    config_nodes::html html_;
};
