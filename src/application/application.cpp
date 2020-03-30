#include "application.h"
#include <memory>

static std::shared_ptr<application> global_application = nullptr;

application::application(const config& conf)
    : ioc_(conf.server_.threads_)
    , listener_(ioc_, boost::asio::ip::tcp::endpoint(conf.server_.address_, conf.server_.port_))
    , html_templates_(conf.html_.redirect_, conf.html_.error404_)
    ,
    //redis_database_(ioc_, boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 6379))
    redis_database_(ioc_, boost::asio::ip::tcp::endpoint(conf.databases_.databases_[0].address_, conf.databases_.databases_[0].port_))
    , logger_()
{
}

application::application(const std::string& config_filename)
    : application(config(config_filename))
{
}

void application::run()
{
    listener_.run();
    ioc_.run();
}

void application::init(const std::string& filename)
{
    global_application = std::make_shared<application>(filename);
}

application& application::get()
{
    return *global_application;
}

int application::main(const std::string& filename)
{
    init(filename);
    get().run();
    return 0;
}
