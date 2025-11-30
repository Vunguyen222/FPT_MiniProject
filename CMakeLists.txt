cmake_minimum_required(VERSION 3.10)
project(Music_Player_App VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/include/model
    ${PROJECT_SOURCE_DIR}/include/controller
    ${PROJECT_SOURCE_DIR}/include/view
    ${PROJECT_SOURCE_DIR}/utils
)
 
 
file(GLOB SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/model/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/controller/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/view/*.cpp"
    "${PROJECT_SOURCE_DIR}/utils/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})