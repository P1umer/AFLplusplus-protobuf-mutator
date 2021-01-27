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

#include "test_fuzzer.h"


namespace test_fuzzer {
namespace {

    TestMessageHandler* GetMessageHandler(){
        static TestMessageHandler mhandler;
        return &mhandler;
    }
}

TestMessageHandler::TestMessageHandler(){
    // Todo
}

TestMessageHandler::~TestMessageHandler(){
    // Todo
}

size_t TestMessageHandler::TransferMessageType(const Root& input, unsigned char **out_buf){
    //unsigned char* t="Test";
    //*out_buf = t;
    return 1;
}

DEFINE_AFL_PROTO_FUZZER(const Root& input, unsigned char **out_buf){
    // transfer the input to some interesting DATA
    // and output the DATA to *out_buf
    
    /*
     * @param[in] Protobuf Buffer containing the test case
     * @param[out] out_buf Pointer to the buffer containing the test case after tranferance. 
     * @return Size of the output buffer after processing or the needed amount.
    */
    GetMessageHandler()->TransferMessageType(input, out_buf); 
}
} // namespace test_fuzzer
