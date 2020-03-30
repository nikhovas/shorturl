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

namespace boost {
namespace property_tree {
    ptree from_json_file(const std::string& filename);
}
}