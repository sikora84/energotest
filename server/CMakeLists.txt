#
# The ADD_EXAMPLE macro (defined in examples/CMakeLists.txt) ensures that
# the example is correctly built for the requested connector. It is equivalent
# to the following two lines:
#   ADD_EXECUTABLE(hello.wt hello.C)
#   TARGET_LINK_LIBRARIES(hello.wt ${EXAMPLES_CONNECTOR})
# except when the ISAPI (for Microsoft IIS) connector is used, where it will
# build a DLL with the proper symbols exported.
#
project(server)
cmake_minimum_required(VERSION 3.10)
link_directories(/usr/local/lib)
SET(WT_LIB wt)
SET(WT_LIB_HTTP wthttp)
SET(WTDBO_LIB wtdbo)
SET(WTDBOSQLITE3_LIB wtdbosqlite3)

set(env_libs crypt pthread dl z)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 -s")

include_directories(${CMAKE_SOURCE_DIR})
ADD_EXECUTABLE(server
        main.cpp
        dbosession.cpp
        user.cpp
        entry.cpp
        restresource.cpp)

TARGET_LINK_LIBRARIES(server ${type} ${WT_LIB} ${WT_LIB_HTTP} ${WTDBO_LIB} ${WTDBOSQLITE3_LIB} ${env_libs})

INCLUDE_DIRECTORIES(/usr/local/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../common)

