cmake_minimum_required(VERSION 3.15)

project(nlptool VERSION 0.1.0)
include(cmake/Common.cmake)

option(BUILD_SHARED_LIBS "Builds shared libaries in addition to static libraries." ON)
message(STATUS "LIBNLP_ENABLE_SHARED= ${LIBNLP_ENABLE_SHARED}")
option(BUILD_TESTS "enable test " OFF)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(test)
endif(BUILD_TESTS)


add_subdirectory(thirdparty)
add_subdirectory(src)
