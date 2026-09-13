cmake_minimum_required(VERSION 3.16)
project(morphology_week1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(morphology_lib
  src/binary_image.cpp
  src/structuring_element.cpp
  src/morphology.cpp
)
target_include_directories(morphology_lib PUBLIC include)
target_compile_options(morphology_lib PRIVATE -Wall -Wextra -Wpedantic)

add_executable(morphology_demo src/main.cpp)
target_link_libraries(morphology_demo PRIVATE morphology_lib)

enable_testing()
add_executable(morphology_tests tests/test_cases.cpp)
target_link_libraries(morphology_tests PRIVATE morphology_lib)
add_test(NAME morphology_tests COMMAND morphology_tests)
