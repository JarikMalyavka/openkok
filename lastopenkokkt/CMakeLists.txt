cmake_minimum_required(VERSION 3.16)

project(lastopenkokkt LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(OPENCV REQUIRED IMPORTED_TARGET opencv5)

add_executable(lastopenkokkt main.cpp)

target_link_libraries(lastopenkokkt PRIVATE PkgConfig::OPENCV)

include(GNUInstallDirs)
install(TARGETS lastopenkokkt
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)