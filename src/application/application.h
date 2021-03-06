#include "../config/config.h"
#include "../database/redis/redis_database.h"
#include "../io/logger.h"
#include "../responses/responses.hpp"
#include "../server/listener.h"
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <cstdlib>

class application {
public:
    explicit application(const std::string& config_filename);
    explicit application(const config& config_);

    void run();

    static void init(const std::string& filename);
    static application& get();
    static int main(const std::string& filename);
    //private:
    boost::asio::io_context ioc_;
    listener listener_;
    html_templates html_templates_;
    redis_database redis_database_;
    logger logger_;
};