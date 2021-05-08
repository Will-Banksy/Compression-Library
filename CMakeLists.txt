# Minimum required version of cmake
cmake_minimum_required(VERSION 3.5)

# ===

set(ProjectName "CompressionLibrary")
set(ProjectVersion "1.0")
set(LibraryName "complib")

set(CMakeFlags "")
set(CMakeDebugFlags "")

option(COMPLIB_STATIC "If true, compiles as a static library, else compiles as a shared library" OFF)

# ===

project("${ProjectName}" VERSION "${ProjectVersion}")

# Project root directory and the source directory src/
set(ProjectDir "${PROJECT_SOURCE_DIR}") # PROJECT_SOURCE_DIR is set by calls to project()
set(SourceDir "${ProjectDir}/src")

# ===

set(Libraries "")

set(SourceFiles
	"${SourceDir}/lzo/LZOCompression.cpp"
	"${SourceDir}/lzo/3rdparty/minilzo.c"
)

set(HeaderFiles
	"${SourceDir}/lzo/LZOCompression.h"
	"${SourceDir}/lzo/3rdparty/minilzo.h"
	"${SourceDir}/lzo/3rdparty/lzoconf.h"
	"${SourceDir}/lzo/3rdparty/lzodefs.h"
)

# ===

set(CMAKE_CXX_FLAGS_DEBUG "${CMakeDebugFlags}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CMakeFlags}")

message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")

if("${COMPLIB_STATIC}")
	add_library("${LibraryName}" STATIC "${SourceFiles}" "${HeaderFiles}")
else()
	add_library("${LibraryName}" SHARED "${SourceFiles}" "${HeaderFiles}")
endif()

target_include_directories("${LibraryName}" PRIVATE "${SourceDir}")

target_link_libraries("${LibraryName}" PRIVATE "${Libraries}")

install(TARGETS ${LibraryName} DESTINATION "${CMAKE_INSTALL_LIBDIR}")