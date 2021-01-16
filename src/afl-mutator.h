// Copyright 2021 P1umer
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef AFLPLUSPLUS_PROTOBUF_MUTATOR_MUTATE_H_
#define AFLPLUSPLUS_PROTOBUF_MUTATOR_MUTATE_H_

#include <stddef.h>

#include <cstdint>
#include <functional>
#include <type_traits>

#include "libprotobuf-mutator/port/protobuf.h"
#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

// Defines custom mutator, crossover and test functions using default
// serialization format. Default is text.
#define DEFINE_AFL_PROTO_FUZZER(args) DEFINE_AFL_TEXT_PROTO_FUZZER(args)
// Defines custom mutator, crossover and test functions using text
// serialization. This format is more convenient to read.
#define DEFINE_AFL_TEXT_PROTO_FUZZER(args) DEFINE_AFL_PROTO_FUZZER_IMPL(false, args)
// Defines custom mutator, crossover and test functions using binary
// serialization. This makes mutations faster. However often test function is
// significantly slower than mutator, so fuzzing rate may stay unchanged.
#define DEFINE_AFL_BINARY_PROTO_FUZZER(args) DEFINE_AFL_PROTO_FUZZER_IMPL(true, args)

// Implementation of macros above.
#define DEFINE_AFL_CUSTOM_PROTO_MUTATOR_IMPL(use_binary, Proto)                    \
  extern "C" size_t afl_custom_fuzz(                                               \
      void *data, unsigned char *buf, size_t buf_size, unsigned char **out_buf,    \
      unsigned char *add_buf, size_t add_buf_size, size_t max_size); {             \
      Proto input1;                                                                \
      Proto input2;                                                                \
      return A_CustomProtoMutator(use_binary, data, buf, buf_size, out_buf,        \
                                  add_buf, add_buf_size, max_size,                 \
                                  &input1, &input2);                               \
      }

#define DEFINE_AFL_CUSTOM_PROTO_POST_PROCESS_IMPL(use_binary, Proto)                 \
  extern "C" size_t afl_custom_post_process(                                         \
      void *data, unsigned char *buf, size_t buf_size, unsigned char **out_buf); {   \
      Proto input;
      // LoadProtoInput(use_binary, data, size, &input)
      // ProtoToDataHelper(input, out_buf);                                          \
      return A_CustomProtoPostProcess(use_binary, data, buf, buf_size,               \
                                      out_buf, &input);                              \                      
      }

#define DEFINE_AFL_PROTO_FUZZER_IMPL(use_binary, arg)                                 \
  void ProtoToDataHelper(args)                                                         \
  using FuzzerProtoType = std::remove_const<std::remove_reference<                    \
      std::function<decltype(ProtoToDataHelper)>::first_argument_type>::type>::type;  \
  DEFINE_AFL_CUSTOM_PROTO_MUTATOR_IMPL(use_binary, FuzzerProtoType)                   \
  DEFINE_AFL_CUSTOM_PROTO_POST_PROCESS_IMPL(use_binary, FuzzerProtoType)              \
  void ProtoToDataHelper(args)

namespace protobuf_mutator{
namespace aflplusplus {

  //Implementation of Crossover and Mutation of test cases in A(FL)_CustomProtoMutator.
  size_t A_CustomProtoMutator(bool binary, void *data, unsigned char *buf, size_t buf_size, 
                              unsigned char **out_buf, unsigned char *add_buf, 
                              size_t add_buf_size, size_t max_size,
                              protobuf::Message* input1,
                              protobuf::Message* input2);

  // A post-processing function to use right before AFL++ writes the test case to
  // disk in order to execute the target.
  size_t A_CustomProtoPostProcess(bool binary, void *data, unsigned char *buf, 
                                  size_t buf_size, unsigned char **out_buf,
                                  protobuf::Message* input);
  

} // namespace aflplusplus
} // namespace protobuf_mutator


#endif // AFLPLUSPLUS_PROTOBUF_MUTATOR_MUTATE_H_