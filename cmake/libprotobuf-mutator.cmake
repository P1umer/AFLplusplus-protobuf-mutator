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
cmake_policy(PUSH)
cmake_policy(SET CMP0074 NEW)
include(ExternalProject)

set(LPM_TARGET libprotobuf-mutator)
set(LPM_EXTERNAL external.lpm)
set(LPM_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/third_party/${LPM_EXTERNAL})

set(LPM_INCLUDE_DIR ${LPM_INSTALL_DIR}/include/libprotobuf-mutator)
set(LPM_LIB_DIR ${LPM_INSTALL_DIR}/lib)

include_directories(${LPM_INCLUDE_DIR})

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget libprotobuf-mutator::protobuf-mutator-libfuzzer libprotobuf-mutator::protobuf-mutator)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)

# Create ${LPM_INCLUDE_DIR}/src to bypass check of INTERFACE_INCLUDE_DIRECTORIES in set_target_properties()
file(MAKE_DIRECTORY ${LPM_INCLUDE_DIR}/src)

# Create imported target libprotobuf-mutator::protobuf-mutator-libfuzzer
add_library(libprotobuf-mutator::protobuf-mutator-libfuzzer STATIC IMPORTED)

set_target_properties(libprotobuf-mutator::protobuf-mutator-libfuzzer PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${LPM_INCLUDE_DIR};${LPM_INCLUDE_DIR}/src"
  INTERFACE_LINK_LIBRARIES "libprotobuf-mutator::protobuf-mutator;protobuf"
)

# Create imported target libprotobuf-mutator::protobuf-mutator
add_library(libprotobuf-mutator::protobuf-mutator STATIC IMPORTED)

set_target_properties(libprotobuf-mutator::protobuf-mutator PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${LPM_INCLUDE_DIR};${LPM_INCLUDE_DIR}/src"
  INTERFACE_LINK_LIBRARIES "protobuf"
)

# Import target "libprotobuf-mutator::protobuf-mutator-libfuzzer" for configuration ""
set_property(TARGET libprotobuf-mutator::protobuf-mutator-libfuzzer APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libprotobuf-mutator::protobuf-mutator-libfuzzer PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${LPM_LIB_DIR}/libprotobuf-mutator-libfuzzer.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libprotobuf-mutator::protobuf-mutator-libfuzzer )
list(APPEND _IMPORT_CHECK_FILES_FOR_libprotobuf-mutator::protobuf-mutator-libfuzzer "${_IMPORT_PREFIX}/lib/libprotobuf-mutator-libfuzzer.a" )

# Import target "libprotobuf-mutator::protobuf-mutator" for configuration ""
set_property(TARGET libprotobuf-mutator::protobuf-mutator APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(libprotobuf-mutator::protobuf-mutator PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${LPM_LIB_DIR}/libprotobuf-mutator.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS libprotobuf-mutator::protobuf-mutator )
list(APPEND _IMPORT_CHECK_FILES_FOR_libprotobuf-mutator::protobuf-mutator "${LPM_LIB_DIR}/libprotobuf-mutator.a" )

set(LPM_GIT_URL      https://github.com/google/libprotobuf-mutator.git)  
set(LPM_GIT_TAG      v1.0)
set(LPM_CONFIGURE    cd ${LPM_INSTALL_DIR}/src/${LPM_TARGET} && ${CMAKE_COMMAND} .                   
                        -DLIB_PROTO_MUTATOR_DOWNLOAD_PROTOBUF=OFF
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
                        -DCMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
                        -DCMAKE_INSTALL_PREFIX=${LPM_INSTALL_DIR} 
                        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER} 
                        -DCMAKE_C_COMPILER=${CMAKE_C_COMPILER}
                        -DCMAKE_C_FLAGS=${CMAKE_C_FLAGS}
                        -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS})
set(LPM_MAKE         cd ${LPM_INSTALL_DIR}/src/${LPM_TARGET} && make)
set(LPM_INSTALL      cd ${LPM_INSTALL_DIR}/src/${LPM_TARGET} && make install)

ExternalProject_Add(    ${LPM_TARGET}
    PREFIX              ${LPM_INSTALL_DIR}
    GIT_REPOSITORY      ${LPM_GIT_URL}
    GIT_TAG             ${LPM_GIT_TAG}         
    CONFIGURE_COMMAND   ${LPM_CONFIGURE}
    BUILD_COMMAND       ${LPM_MAKE}
    INSTALL_COMMAND     ${LPM_INSTALL}
)

if(LIB_PROTOBUF_DOWNLOAD)
    add_dependencies(${LPM_TARGET} ${PROTOBUF_TARGET})
else()
    include(CMakeFindDependencyMacro)
    find_dependency(Protobuf REQUIRED)
endif()

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)

cmake_policy(POP)





