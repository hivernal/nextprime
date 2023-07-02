cmake_minimum_required(VERSION 3.2)
project(nextprime CXX)

set(SRC
    src/main.cpp
    src/bignums.cpp
    src/thread.cpp
    src/diemitko.cpp
    )
set(INCLUDE
    include
    )

add_executable(nextprime ${SRC})
target_include_directories(nextprime PRIVATE ${INCLUDE})
target_link_libraries(nextprime PRIVATE gmp boost_thread)
