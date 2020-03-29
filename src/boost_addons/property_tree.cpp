#include "property_tree.h"

namespace boost {
    namespace property_tree {
        ptree from_json_file(const std::string& filename) {
            ptree pt;
            read_json(filename, pt);
            return pt;
        }
    }
}