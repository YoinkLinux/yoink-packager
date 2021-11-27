project(yoink)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
add_executable(
        yoink
        src/yoink.cpp
        src/package.cpp
        include/package.h
        src/database.cpp
        include/database.h)
target_link_libraries(yoink sqlite3)
target_include_directories(yoink PRIVATE include)
