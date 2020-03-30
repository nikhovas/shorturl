cmake_minimum_required(VERSION 3.10)
project(shorturl)

include(GNUInstallDirs)
find_package(Boost COMPONENTS system)
find_package(Threads)

aux_source_directory(. SRC_LIST)

add_executable(shorturl ${SRC_LIST} src/server/session.h src/server/session.cpp src/server/listener.h src/server/listener.cpp
        src/responses/responses.hpp src/responses/responses.cpp src/config/config.h src/config/config.cpp
        src/config/config_elements.h src/config/config_elements.cpp
        src/boost_addons/property_tree.h src/boost_addons/property_tree.cpp
        src/application/application.h src/application/application.cpp
        src/database/redis/redis_database.h src/database/redis/redis_database.cpp
        src/io/logger.cpp src/io/logger.h src/main.cpp)

set(CMAKE_CXX_STANDARD 14)
message(STATUS "C++: ${CMAKE_CXX_COMPILER_VERSION}")

include_directories("libs/cpp-bredis/include")
target_link_libraries(${PROJECT_NAME} PRIVATE ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

message(STATUS "---------------------")
message(STATUS "Boost_FOUND: ${Boost_FOUND}")
message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
message(STATUS "---------------------")

add_subdirectory(tests)