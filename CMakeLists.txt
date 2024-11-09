cmake_minimum_required(VERSION 3.10)
project (Notes)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

include (FetchContent)
FetchContent_Declare (
  argparse
  GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable (argparse)

FetchContent_Declare (
  json
  URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz
)
FetchContent_MakeAvailable(json)


include_directories (include)
file (GLOB_RECURSE SOURCES "src/*.cpp")
add_executable (notes ${SOURCES})
target_link_libraries (notes argparse nlohmann_json::nlohmann_json)
target_include_directories (notes PRIVATE
  ${CMAKE_SOURCE_DIR}/include
  ${argparse_SOURCE_DIR}/include
  ${json_SOURCE_DIR}/include

)
