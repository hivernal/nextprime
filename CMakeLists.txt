cmake_minimum_required(VERSION 3.2)
project(nextprime C)

set(SRC
    src/main.c
    src/diemitko.c
    )

set(INCLUDE
    ${CMAKE_CURRENT_SOURCE_DIR}
    include
    )

add_executable(nextprime ${SRC})
target_link_libraries(nextprime PRIVATE gmp)
target_include_directories(nextprime PRIVATE ${INCLUDE})
