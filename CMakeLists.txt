cmake_minimum_required(VERSION 3.4.2)
project(thpool2)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_DESCRIPTION "Implementation of thread pool runtime to support dynamically fork-join application.")
set(PROJECT_URL "https://github.com/Arka2009/thpool2")
set(THPOOL2_VERSION_MAJOR 1)
set(THPOOL2_VERSION_MINOR 0)
set(THPOOL2_INSTALL_INCLUDEDIR "/usr/local/include/thpool2")
set(THPOOL2_INSTALL_LIBDIR "/usr/local/lib")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file(
  "${PROJECT_SOURCE_DIR}/ThPool2Config.h.in"
  "${PROJECT_BINARY_DIR}/ThPool2Config.h"
  )
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.c")
 
# Target
set(TGTLIB thpool2)
add_library(${TGTLIB} STATIC ${SOURCES})
target_include_directories(${TGTLIB} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR})
target_compile_options(${TGTLIB} PRIVATE -Wall -Wextra -fno-strict-aliasing)

# Test target
set(TESTEXE ecolibtest)
add_executable(${TESTEXE} ${SOURCES} ${PROJECT_SOURCE_DIR}/test/ecolibtest.c)
target_include_directories(${TESTEXE} PUBLIC ${PROJECT_SOURCE_DIR}/include ${PROJECT_BINARY_DIR})
target_compile_options(${TESTEXE} PRIVATE -Wall)

# Install
include(GNUInstallDirs)
install(TARGETS TGTLIB DESTINATION "${THPOOL2_INSTALL_LIBDIR}")
install(FILES
    ${PROJECT_BINARY_DIR}/ThPool2Config.h
    DESTINATION ${THPOOL2_INSTALL_INCLUDEDIR})
