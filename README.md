# AFLplusplus-protobuf-mutator
AFLplusplus + libprotobuf-mutator 
## Overview
[AFLplusplus-protobuf-mutator](https://github.com/P1umer/AFLplusplus-protobuf-mutator) integrates [AFLplusplus](https://github.com/AFLplusplus/AFLplusplus) and [libprotobuf-mutator](https://github.com/google/libprotobuf-mutator).
It could be used to feed the target on INTERESTING data based on protobuf.

## Quick start
### Download source code && update submodule
```
git clone https://github.com/P1umer/AFLplusplus-protobuf-mutator.git
cd AFLplusplus-protobuf-mutator
git submodule update
```
### Build
First, build `/libprotobuf-mutator` according to instructions [here](https://github.com/google/libprotobuf-mutator#quick-start-on-debianubuntu).
Then, use CMake to compile everything.
```
mkdir build
cd build
cmake ..
make
```

## Usage
Simply include [afl-mutator.h](https://github.com/P1umer/AFLplusplus-protobuf-mutator/blob/main/src/afl-mutator.h).For example:
```
#include "src/afl-mutator.h"

DEFINE_AFL_PROTO_FUZZER(const MessageType& input, unsigned char **out_buf){
    // transfer the input to some interesting DATA
    // and output the DATA to *out_buf
    
    /*
     * @param[in] Protobuf Buffer containing the test case
     * @param[out] out_buf Pointer to the buffer containing the test case after tranferance. 
     * @return Size of the output buffer after processing or the needed amount.
    */
    TransferMessageType(input, out_buf); 
}
```