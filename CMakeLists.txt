cmake_minimum_required(VERSION 3.2)
project (Kafkanator)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


set(CEREAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/cereal/include)
set(CATCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/catch/include)


add_subdirectory(external)

add_subdirectory(src)


find_package(Doxygen)
