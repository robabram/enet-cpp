# ENet-CPP
A C++20 "Greenfield" implementation of the ENet reliable UDP networking library ([lsalzman/enet](https://github.com/lsalzman/enet)). 

## Background
My son is interested in game development and we are planning on working on a game together. It has been
a number of years (pre C++11) since I have last done any C++ development. And after reading the latest "A Tour of C++" by Bjarne Stroustrup,
I realized that the C++ language and standard library have greatly changed for the better and I have a lot to learn. 

Reimplementing the ENet library in C++20 is a project to help me sharpen my rusty C++ skills, 
learn C++20 coding patterns and help prepare the way for doing some game development with my son,

## Goals

* Complete "Greenfield" implementation of the ENet library in C++20
* Match the ENET network protocol as the only legacy component (IE: a "C" ENet peer should be
able to connect and function with this ENet C++ library)
* IPv6 support
* Unix and Win32 builds
* Dynamic and Shared library builds
* Multi-threaded, each network socket will get a worker thread. Passing data between threads will be minimized
to prevent significant thread context switching performance penalties (Possibly support a single threaded version)
* Unittests

## Roadmap

1. ~~Basic library structure that can connect to a socket~~
2. Multi-peer ping test
3. Packet queuing, single peer and all peer broadcasting
4. Support ENet networking protocol
5. (Profit)
6. Performance and valgrind testing
7. ...
8. Rework README with build, install and code examples
9. Setup online documentation

## Contributions and Suggestions
This project is just getting started, but if you are interested in contributing please read the 
CONTRIBUTING.md located in the root this project. 

