cmake_minimum_required(VERSION 3.11)

project(mandor)

# "How can I change compilers in CLion?"
# [ https://intellij-support.jetbrains.com/hc/en-us/articles/207251865-How-can-I-change-compilers-in-CLion-
#   === https://goo.gl/V4qzZU ]

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(src/easylogging)

add_executable(mandor
        src/easylogging/easylogging++.cc
        src/easylogging/easylogging++.h
        src/em.cpp
        src/em.h
        src/main.cpp
        src/PeriodicBoundaryConditions.cpp
        src/PeriodicBoundaryConditions.h
        src/planeWave.cpp
        src/planeWave.h
        src/testConstMacros.h
        src/type_mesh.h
        src/type_vector.cpp
        src/type_vector.h)
