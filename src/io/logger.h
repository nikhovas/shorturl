#pragma once

#include <string>
#include <boost/asio.hpp>

enum logger_mode {
    LOG_ERRORS = 0b0001,
    LOG_REQUESTS = 0b0010,

    LOG_CONSOLE = 0b0100,
    LOG_FILE = 0b1000
};

class logger {
public:
    logger(const logger_mode& logger_mode_ = static_cast<logger_mode>(LOG_ERRORS | LOG_CONSOLE | LOG_FILE));
    void log_raw(const std::string& msg, const std::string& type_str = "[INF]");

    template<typename protocol>
    void log_network_event(const std::string& msg, const boost::asio::ip::basic_endpoint<protocol>& endpoint) {
        std::string protocol_name = "[UNK ";
        if (std::is_same<protocol, boost::asio::ip::tcp>::value) {
            protocol_name = "[TCP ";
        } else if (std::is_same<protocol, boost::asio::ip::udp>::value) {
            protocol_name = "[UDP ";
        }
        log_raw(protocol_name + endpoint.address().to_string() + ":" + std::to_string(endpoint.port()) + "] " + msg);
    }
    void error(const std::string& msg);

    template<typename protocol>
    void error_event(const std::string& msg, const boost::asio::ip::basic_endpoint<protocol>& endpoint) {
        std::string protocol_name = "[UNK ";
        if (std::is_same<protocol, boost::asio::ip::tcp>::value) {
            protocol_name = "[TCP ";
        } else if (std::is_same<protocol, boost::asio::ip::udp>::value) {
            protocol_name = "[UDP ";
        }
        error(protocol_name + endpoint.address().to_string() + ":" + std::to_string(endpoint.port()) + "] " + msg);
    }
private:
    logger_mode logger_mode_;
};