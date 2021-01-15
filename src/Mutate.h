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

#include "libprotobuf-mutator/src/libfuzzer/libfuzzer_macro.h"

// Defines custom mutator, crossover and test functions using default
// serialization format. Default is text.
#define DEFINE_AFL_PROTO_FUZZER(arg) DEFINE_AFL_TEXT_PROTO_FUZZER(arg)
// Defines custom mutator, crossover and test functions using text
// serialization. This format is more convenient to read.
#define DEFINE_AFL_TEXT_PROTO_FUZZER(arg) DEFINE_AFL_PROTO_FUZZER_IMPL(false, arg)
// Defines custom mutator, crossover and test functions using binary
// serialization. This makes mutations faster. However often test function is
// significantly slower than mutator, so fuzzing rate may stay unchanged.
#define DEFINE_AFL_BINARY_PROTO_FUZZER(arg) DEFINE_AFL_PROTO_FUZZER_IMPL(true, arg)

// Implementation of macros above.
#define DEFINE_AFL_CUSTOM_PROTO_MUTATOR_IMPL(use_binary, Proto)                        \
  extern "C" size_t afl_custom_fuzz(                                               \
      void *data, unsigned char *buf, size_t buf_size, unsigned char **out_buf,    \
      unsigned char *add_buf, size_t add_buf_size, size_t max_size); {             \
      return A_CustomProtoMutator(void *data, unsigned char *buf, size_t buf_size, \
                                  unsigned char **out_buf, unsigned char *add_buf, \
                                  size_t add_buf_size, size_t max_size);           \
      }

#define DEFINE_AFL_PROTO_FUZZER_IMPL(use_binary, arg)                              \
  static void ProtoToDataHelper(arg);                                              \
  using FuzzerProtoType = std::remove_const<std::remove_reference<                 \
      std::function<decltype(ProtoToDataHelper)>::argument_type>::type>::type;     \
  DEFINE_AFL_CUSTOM_PROTO_MUTATOR_IMPL(use_binary, FuzzerProtoType)                \
  static void ProtoToDataHelper(arg)

namespace aflplusplus_custom_mutator{
  
  //Implementation of Crossover and Mutation of test cases in A(FL)_CustomProtoMutator.
  size_t A_CustomProtoMutator(void *data, unsigned char *buf, size_t buf_size, 
                              unsigned char **out_buf, unsigned char *add_buf, 
                              size_t add_buf_size, size_t max_size);
} //

#endif // AFLPLUSPLUS_PROTOBUF_MUTATOR_MUTATE_H_