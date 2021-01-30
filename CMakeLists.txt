# Copyright 2021 P1umer
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(AFLplusplus-protobuf-mutator CXX)

enable_language(C)
enable_language(CXX)

# set c++ version
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

OPTION(LIB_PROTOBUF_DOWNLOAD
       "Automatically download working Protobuf" ON)

OPTION(LIB_PROTOBUF_MUTATOR_DOWNLOAD
       "Automatically download working LPM" ON)

# External dependencies
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

# External dependencies
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# check -fPIC
set(CMAKE_REQUIRED_FLAGS "-fPIC")
check_cxx_compiler_flag(-fPIC PIC)
unset(CMAKE_REQUIRED_FLAGS)

if (PIC)
    set(EXTRA_FLAGS "${EXTRA_FLAGS} -fPIC")
endif()

set(C_EXTRA_FLAGS "${C_EXTRA_FLAGS} ${EXTRA_FLAGS}")
set(CXX_EXTRA_FLAGS "${CXX_EXTRA_FLAGS} ${EXTRA_FLAGS}")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_EXTRA_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX_EXTRA_FLAGS}")

set(PROTOBUF_CFLAGS "${CMAKE_C_FLAGS} ${NO_FUZZING_FLAGS} -w")
set(PROTOBUF_CXXFLAGS "${CMAKE_CXX_FLAGS} ${NO_FUZZING_FLAGS} -w")
if(CMAKE_USE_PTHREADS_INIT)
  set(PROTOBUF_CFLAGS "${PROTOBUF_CFLAGS} -pthread")
  set(PROTOBUF_CXXFLAGS "${PROTOBUF_CXXFLAGS} -pthread")
endif()

if (LIB_PROTOBUF_DOWNLOAD)
  include(libprotobuf)
else()
  find_package(Protobuf REQUIRED)
  include_directories(${PROTOBUF_INCLUDE_DIRS})
  include_directories(${CMAKE_CURRENT_BINARY_DIR})
endif()

if(LIB_PROTOBUF_MUTATOR_DOWNLOAD)
    include(libprotobuf-mutator)
else()
    find_package(libprotobuf-mutator REQUIRED)
    message("${libprotobuf-mutator_FOUND}")
    if(libprotobuf-mutator_FOUND)
        get_filename_component(_IMPORT_PREFIX "${libprotobuf-mutator_DIR}" PATH)
        get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
        get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
        SET(LPM_INCLUDE_DIRS "${_IMPORT_PREFIX}/include/libprotobuf-mutator")
    endif(libprotobuf-mutator_FOUND)
endif()

add_subdirectory(src)
add_subdirectory(example)








