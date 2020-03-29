#include "logger.h"

#include <chrono>
#include <iomanip>
#include <iostream>


logger::logger(const logger_mode& logger_mode_) {

}

void logger::log_raw(const std::string& msg, const std::string& type_str) {
    auto now = std::chrono::system_clock::now();
    std::time_t t_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::cout << type_str + " [" << std::put_time(std::localtime(&t_c), "%F %T") << "] " << msg << std::endl;
}

void logger::error(const std::string& msg) {
    log_raw(msg, "[ERR]");
}