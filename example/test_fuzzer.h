// Copyright 2021 P1umer

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef AFLPLUSPLUS_PROTOBUF_MUTATOR_EXAMPLE_TEST_FUZZER_H_
#define AFLPLUSPLUS_PROTOBUF_MUTATOR_EXAMPLE_TEST_FUZZER_H_

#include "gen/test.pb.h"
#include "src/afl_mutator.h"

namespace test_fuzzer {

    class TestMessageHandler{
        public:
            TestMessageHandler();
            ~TestMessageHandler();
            size_t TransferMessageType(const Root& input, unsigned char **out_buf);

    };

} //namespace test_fuzzer


#endif // AFLPLUSPLUS_PROTOBUF_MUTATOR_EXAMPLE_TEST_FUZZER_H_