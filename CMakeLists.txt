cmake_minimum_required(VERSION 3.29)
project(enet_cpp
        VERSION 0.1.1
        DESCRIPTION "C++20 Reliable UDP Networking Library"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

add_library(enet_cpp SHARED
        include/enet_cpp/socket.h
        include/enet_cpp/unix.h
        include/enet_cpp/win32.h
        src/enet.cpp
        src/host.cpp
        src/socket.cpp
)

set_target_properties(enet_cpp PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(enet_cpp PROPERTIES
        PUBLIC_HEADER include/enet_cpp/enet.h
)

configure_file(enet_cpp.pc.in enet_cpp.pc @ONLY)

target_include_directories(enet_cpp PRIVATE include)
target_include_directories(enet_cpp PRIVATE src)

if (WIN32)
    target_link_libraries(enet_cpp winmm ws2_32)
endif()

include(GNUInstallDirs)
install(TARGETS enet_cpp
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
