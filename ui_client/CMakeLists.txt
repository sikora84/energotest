cmake_minimum_required(VERSION 3.5)

project(ui_client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -O3 -s")
set(env_libs curl jsoncpp)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

add_executable(ui_client main.cpp library.cpp library_wrap.cpp qml.qrc)

target_compile_definitions(ui_client
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ui_client
  PRIVATE ${type} ${env_libs} Qt5::Core Qt5::Quick)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/../common)
