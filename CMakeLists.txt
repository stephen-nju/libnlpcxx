cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(nlptool VERSION 0.1.0)

# global options
option(ENABLE_CPPCHECK "Enable static analysis with cppcheck" OFF)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" OFF)
# cppcheck
option(BUILD_SHARED_LIBS "Builds shared libaries in addition to static libraries." ON)
message(STATUS "BUILD_SHARED_LIBS= ${BUILD_SHARED_LIBS}")
option(ENABLE_BUILD_TESTS "enable project test" ON)
# BUILDS_TESTS变量冲突
message(STATUS "BUILD_TESTS= ${ENABLE_BUILD_TESTS}")




include(cmake/Common.cmake)
include(cmake/Sanitizers.cmake)
include(cmake/StaticAnalyzers.cmake)



if(ENABLE_BUILD_TESTS)
  MESSAGE( STATUS  "enable build project  ctest")
  enable_testing()
  add_subdirectory(test)
endif(ENABLE_BUILD_TESTS)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)



add_subdirectory(thirdparty)
add_subdirectory(src)
