cmake_minimum_required(VERSION 3.2)
project(nextprime CXX)

set(SRC
    src/main.cpp
    src/bignums.cpp
    src/diemitko.cpp
    src/thread.cpp
    )

set(INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
    )

add_executable(nextprime ${SRC})
target_link_libraries(nextprime PRIVATE gmp gmpxx)
target_include_directories(nextprime PRIVATE ${INCLUDE})
