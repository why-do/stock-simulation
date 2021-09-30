cmake_minimum_required(VERSION 3.0.0)
project(stock-simulation VERSION 0.1.0)

include(CTest)
enable_testing()

aux_source_directory(. DIRSRCS)

add_executable(${PROJECT_NAME} ${DIRSRCS})

target_link_libraries( ${PROJECT_NAME}
        ws2_32)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

