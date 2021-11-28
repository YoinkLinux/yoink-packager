project(yoink-installer)
add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 20)
add_executable(
        yoink-installer
        yoinkinstaller.cpp
        ../package.cpp
        ../database.cpp
)
target_link_libraries(yoink-installer sqlite3 curl)
target_include_directories(yoink-installer PRIVATE ../../include)
