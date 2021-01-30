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

protobuf_generate_cpp(
            TEST_PROTO_SRC 
            TEST_PROTO_HDR
            test.proto)

set(TEST_SRC test_fuzzer.cc)
add_library(test-fuzzer SHARED 
            ${TEST_SRC}
            ${TEST_PROTO_SRC})
add_dependencies(test-fuzzer aflpm)
target_link_libraries(test-fuzzer aflpm)