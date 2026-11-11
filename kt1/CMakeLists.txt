cmake_minimum_required(VERSION 3.16)

project(kt1 LANGUAGES CXX)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kt1 main.cpp)
target_link_libraries(kt1 PRIVATE PkgConfig::OPENCV)
include(GNUInstallDirs)
install(TARGETS kt1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
