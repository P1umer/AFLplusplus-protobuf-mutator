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

add_subdirectory(Fuzzer)
set(LIBAFLPM_SRC afl_mutator.cc)
add_library(aflpm STATIC ${LIBAFLPM_SRC})
if(LIB_PROTOBUF_MUTATOR_DOWNLOAD)
    add_dependencies(aflpm libprotobuf-mutator Fuzzer)
endif()
target_link_libraries(aflpm libprotobuf-mutator::protobuf-mutator-libfuzzer)
target_link_libraries(aflpm Fuzzer)
