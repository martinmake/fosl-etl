#######################################################################
# The Embedded Template Library (https://www.etlcpp.com/)
#######################################################################
cmake_minimum_required(VERSION 3.5.0)
project(fosl-etl)

#######################################################################
# Define an option to allow consumers of the library to
# specify the profile they would like to compile to.  If
# not explicitly set CMake will attempt to choose an appropriate
# profile based on the compiler
#######################################################################
set(ETL_PROFILE "DEFAULT" CACHE STRING "Defines what profile header to include.  See https://www.etlcpp.com/setup.html"
)

option(BUILD_TESTS "Build unit tests" OFF)

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME}
  INTERFACE
  include/fosl
  include/fosl/etl/profiles
  )

if (${ETL_PROFILE} STREQUAL DEFAULT)
  if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(ETL_PROFILE "PROFILE_GCC_GENERIC")

  elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(ETL_PROFILE "PROFILE_CLANG_GENERIC")

  elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(ETL_PROFILE "PROFILE_MSVC")

  elseif (CMAKE_CXX_COMPILER_ID MATCHES "ARMCC")
    if (CXX_STANDARD EQUAL 11)
      set(ETL_PROFILE "PROFILE_ARMV6")
    else ()
      set(ETL_PROFILE "PROFILE_ARMV5")
    endif()
  elseif (CMAKE_CXX_COMPILER_ID MATCHES "TI")
    set(ETL_PROFILE "PROFILE_TICC")

  else()
    message(FATAL_ERROR "Can't generate default profile for compiler: ${CMAKE_CXX_COMPILER_ID}")
  endif()
endif()

message(STATUS "Compiling with ETL profile set to: ${ETL_PROFILE}")

target_compile_definitions(${PROJECT_NAME}
  INTERFACE
  ${ETL_PROFILE}
  )



if (BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
