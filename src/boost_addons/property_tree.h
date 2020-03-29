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

namespace boost {
    namespace property_tree {
        ptree from_json_file(const std::string& filename);
    }
}