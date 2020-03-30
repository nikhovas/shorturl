#include "application/application.h"
#include <string>

int main(int argc, char* argv[])
{
    std::string config_filename = argc == 1 ? "../data/config.json" : argv[1];
    application::init(config_filename);
    application::get().run();
    return 0;
}