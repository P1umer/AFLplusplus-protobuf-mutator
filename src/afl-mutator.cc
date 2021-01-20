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

#include <random>
#include <algorithm>

#define INITIAL_SIZE (100)
#define MAX_LENGTH(x, y) ( ((x) > (y)) ? (x) : y )

namespace protobuf_mutator{
namespace aflplusplus {
namespace {

    size_t GetRandom(size_t s){
        static std::default_random_engine generator(s);
        std::uniform_int_distribution<size_t> uniform_dist(1, 10);
        return uniform_dist(generator);
    }

} // namespace

    MutateHelper::MutateHelper(size_t s) {
        buf_  = static_cast<uint8_t*>(calloc(1, INITIAL_SIZE));
        if(!buf_) perror("MutateHelper init");
        seed_ = s;
    }

    uint8_t* MutateHelper::ReallocBuf(size_t length) {
        len_ = MAX_LENGTH(length, INITIAL_SIZE);
        buf_ = static_cast<uint8_t*>(realloc(buf_, len_));
        if(!buf_) perror("MutateHelper realloc");
        return buf_;
    }

    size_t A_CustomProtoMutator(MutateHelper *m, bool binary, unsigned char *buf, size_t buf_size, 
                                unsigned char **out_buf, unsigned char *add_buf, 
                                size_t add_buf_size, size_t max_size, 
                                protobuf::Message* input1,
                                protobuf::Message* input2) {                   
        using libfuzzer::CustomProtoMutator;
        using libfuzzer::CustomProtoCrossOver; 

        // (PC) probability of crossover : 0.8 (0.6~1.0)
        // (PM) probability of mutation  : 0.2 
        switch (GetRandom(m->GetSeed())){
            case 1:
            case 2:{
                // copy to m.buf_
                memcpy(m->ReallocBuf(std::max(max_size, buf_size)), buf, buf_size);
                m->SetLen(CustomProtoMutator(binary, buf, buf_size, max_size, 
                                             m->GetSeed(), input1));
                break;
            }
            default:{
                m->ReallocBuf(std::max(max_size, std::max(buf_size, add_buf_size)));
                m->SetLen(CustomProtoCrossOver(binary, buf, buf_size, add_buf, add_buf_size, m->GetOutBuf(), 
                                               max_size,m->GetSeed(), input1, input2));
                break;
            }
        }

        *out_buf = m->GetOutBuf();
        return m->GetLen();
    }

} // aflplusplus
} // protobuf_mutator

#undef INITIAL_SIZE




