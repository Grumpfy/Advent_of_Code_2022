cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(aoc_2022 LANGUAGES CXX C)

# global compilation flags
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Xlinker -no_deduplicate")
add_compile_options(-fsanitize=address,undefined)
add_link_options(-fsanitize=address,undefined)

# project options
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

# project warnings
add_library(project_warnings INTERFACE)
target_compile_options(
  project_warnings
  INTERFACE 
  -Wall
  -Wextra # reasonable and standard
  -Wextra-semi # Warn about semicolon after in-class function definition.
  -Wshadow # warn the user if a variable declaration shadows one from a parent context
  -Wnon-virtual-dtor # warn the user if a class with virtual functions has a non-virtual destructor. This helps
  # catch hard to track down memory errors
  -Wold-style-cast # warn for c-style casts
  -Wcast-align # warn for potential performance problem casts
  -Wunused # warn on anything being unused
  -Woverloaded-virtual # warn if you overload (not override) a virtual function
  -Wpedantic # warn if non-standard C++ is used
  -Wconversion # warn on type conversions that may lose data
  -Wsign-conversion # warn on sign conversions
  -Wnull-dereference # warn if a null dereference is detected
  -Wdouble-promotion # warn if float is implicit promoted to double
  -Wformat=2 # warn on security issues around functions that format output (ie printf)
  -Wimplicit-fallthrough # warn on statements that fallthrough without an explicit annotation
  # warning as error
  -Werror
)

# third parties
include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt
  GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(
  cppcoro
  GIT_REPOSITORY https://github.com/lewissbaker/cppcoro
  GIT_TAG 391215262bd40d68ac6534810164131f5f9eb148)
FetchContent_GetProperties(cppcoro)
if(NOT cppcoro_POPULATED)
    FetchContent_Populate(cppcoro)
endif()
add_library(cppcoro INTERFACE)
target_include_directories(cppcoro SYSTEM INTERFACE "${cppcoro_SOURCE_DIR}/include")

FetchContent_Declare(
  range_v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3
  GIT_TAG 0.12.0)
FetchContent_GetProperties(range_v3)
if(NOT range_v3_POPULATED)
    FetchContent_Populate(range_v3)
endif()
add_library(range_v3 INTERFACE)
target_include_directories(range_v3 SYSTEM INTERFACE "${range_v3_SOURCE_DIR}/include")

FetchContent_Declare(
  ctre
  GIT_REPOSITORY https://github.com/hanickadot/compile-time-regular-expressions
  GIT_TAG v3.7.1)
FetchContent_GetProperties(ctre)
if(NOT ctre_POPULATED)
    FetchContent_Populate(ctre)
endif()
add_library(ctre INTERFACE)
target_include_directories(ctre SYSTEM INTERFACE "${ctre_SOURCE_DIR}/single-header")

FetchContent_Declare(
  abseil
  GIT_REPOSITORY https://github.com/abseil/abseil-cpp
  GIT_TAG 296abbd35a600785d6297738749336061ecb2221)
FetchContent_GetProperties(abseil)
if(NOT abseil_POPULATED)
    FetchContent_Populate(abseil)
	set(ABSL_PROPAGATE_CXX_STD ON)
	add_subdirectory(${abseil_SOURCE_DIR} ${abseil_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
add_library(abseil INTERFACE)
target_link_libraries(abseil INTERFACE absl::flat_hash_map)
target_include_directories(abseil SYSTEM INTERFACE "${abseil_SOURCE_DIR}")

add_library(project_third_parties INTERFACE)
target_link_libraries(project_third_parties INTERFACE fmt::fmt cppcoro range_v3 ctre abseil)

# puzzles
add_executable(00_test 00_test.cpp)
target_link_libraries(00_test PRIVATE project_options project_warnings project_third_parties)

add_executable(01_calorie_counting_1 01_calorie_counting_1.cpp)
target_link_libraries(01_calorie_counting_1 PRIVATE project_options project_warnings project_third_parties)

add_executable(01_calorie_counting_2 01_calorie_counting_2.cpp)
target_link_libraries(01_calorie_counting_2 PRIVATE project_options project_warnings project_third_parties)

add_executable(02_rock_paper_scissors_1 02_rock_paper_scissors_1.cpp)
target_link_libraries(02_rock_paper_scissors_1 PRIVATE project_options project_warnings project_third_parties)

add_executable(02_rock_paper_scissors_2 02_rock_paper_scissors_2.cpp)
target_link_libraries(02_rock_paper_scissors_2 PRIVATE project_options project_warnings project_third_parties)

add_executable(03_rucksack_reorganization 03_rucksack_reorganization.cpp)
target_link_libraries(03_rucksack_reorganization PRIVATE project_options project_warnings project_third_parties)

add_executable(03_rucksack_reorganization_2 03_rucksack_reorganization_2.cpp)
target_link_libraries(03_rucksack_reorganization_2 PRIVATE project_options project_warnings project_third_parties)
