SET(TEST_CC test_fuzzer.cc)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/libprotobuf-mutator
)

ADD_LIBRARY(test-fuzzer SHARED ${TEST_CC})
# SET_TARGET_PROPERTIES(test-fuzzer PROPERTIES OUTPUT_NAME "test-fuzzer")