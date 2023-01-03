cmake_minimum_required(VERSION 3.19.6)

project(testPipe)

set(CMAKE_CXX_STANDARD 14)

set(Boost_USE_STATIC_LIBS        ON)

set(RT_LIBRARIES /usr/lib/x86_64-linux-gnu/librt.so)

find_package(Boost REQUIRED) 
find_package(Threads)
find_package(Boost REQUIRED COMPONENTS
program_options filesystem thread system context serialization)


add_executable(Server exampleserver.cpp)
add_executable(Prog main.cpp)

if(UNIX AND NOT APPLE)
	target_link_libraries(Server Boost::program_options Boost::filesystem Boost::thread rt Boost::serialization)
	target_link_libraries(Prog Boost::program_options Boost::filesystem Boost::thread rt Boost::serialization)
endif()

if(MSVC)
	target_link_libraries(Server Boost::program_options Boost::filesystem Boost::thread)
	target_link_libraries(Prog Boost::program_options Boost::filesystem Boost::thread)
endif()
