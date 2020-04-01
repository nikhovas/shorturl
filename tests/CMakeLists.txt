project(Google_tests)

add_subdirectory(googletest)
find_package(Boost 1.67 COMPONENTS system REQUIRED)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run unit_tests.cpp)
target_link_libraries(Google_Tests_run PRIVATE ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} gtest gtest_main)
target_include_directories(Google_Tests_run PRIVATE ${Boost_INCLUDE_DIR})
target_compile_definitions(Google_Tests_run PRIVATE REDIS_IP="127.0.0.1" REDIS_PORT=6379)