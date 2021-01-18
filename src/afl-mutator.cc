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

#include "src/afl-mutator.h"

#include<random>

namespace protobuf_mutator{
namespace aflplusplus {
namespace {
    
} //namespace

    Seed::Seed(size_t s){
        seed_ = s;
    }

    size_t Seed::GetSeed(){
        return seed_;
    }

    size_t A_CustomProtoMutator(bool binary, void *data, unsigned char *buf, size_t buf_size, 
                                unsigned char **out_buf, unsigned char *add_buf, 
                                size_t add_buf_size, size_t max_size, Seed* s,
                                protobuf::Message* input1,
                                protobuf::Message* input2) {                   
        using libfuzzer::CustomProtoMutator;
        using libfuzzer::CustomProtoCrossOver; 

        s->GetSeed();

        // (PC) probability of crossover : 0.8 (0.6~1.0)
        // (PM) probability of mutation  : 0.2 

    }

    // size_t A_CustomProtoPostProcess(bool binary, void *data, unsigned char *buf, 
    //                                 size_t buf_size, unsigned char **out_buf,
    //                                 protobuf::Message* input) {



    // }

    
} // aflplusplus
} // protobuf_mutator






