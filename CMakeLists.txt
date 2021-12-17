cmake_minimum_required(VERSION 3.7)

project(entt_dino LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_source_files_properties(*.cc LANGUAGE CXX)
set_source_files_properties(*.h LANGUAGE CXX)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(ext EXCLUDE_FROM_ALL)
#find_package(SDL2 REQUIRED)

file(GLOB_RECURSE SOURCE_FILES
  "${PROJECT_SOURCE_DIR}/src/*.cc"
  "${PROJECT_SOURCE_DIR}/src/*.h"
)

include_directories(${SDL2_INCLUDE_DIR} "${CMAKE_SOURCE_DIR}/src")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} EnTT spdlog ${SDL2_LIBRARIES} SDL2_image)

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
  target_compile_definitions(${PROJECT_NAME} PRIVATE SPDLOG_ACTIVE_LEVEL "SPDLOG_LEVEL_DEBUG")
  set_directory_properties(PROPERTIES COMPILE_DEFINITIONS "_DEBUG")
endif ()
