cmake_minimum_required(VERSION 3.10)
project(shorturl)

set(CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
find_package(Boost 1.67 COMPONENTS system REQUIRED)
find_package(Threads)

set(SOURCE_FILES "src/server/session.cpp" "src/server/listener.cpp" "src/responses/responses.cpp"
        "src/config/config.cpp" "src/config/config_elements.cpp" "src/boost_addons/property_tree.cpp"
        "src/application/application.cpp" "src/database/redis/redis_database.cpp" "src/io/logger.cpp" "src/main.cpp")

set(HEADER_FILES "src/server/session.h" "src/server/listener.h" "src/responses/responses.hpp" "src/config/config.h"
        "src/config/config_elements.h" "src/boost_addons/property_tree.h" "src/application/application.h"
        "src/database/redis/redis_database.h")

add_executable(shorturl ${SOURCE_FILES} ${HEADER_FILES})

include_directories("libs/cpp-bredis/include")
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

add_subdirectory(tests)
