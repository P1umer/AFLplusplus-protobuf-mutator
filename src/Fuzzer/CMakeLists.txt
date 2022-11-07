set(LIBFUZZER_SOURCES
  FuzzerCrossOver.cpp
  FuzzerDataFlowTrace.cpp
  FuzzerDriver.cpp
  FuzzerExtFunctionsDlsym.cpp
  FuzzerExtFunctionsWeak.cpp
  FuzzerExtFunctionsWindows.cpp
  FuzzerExtraCounters.cpp
  FuzzerFork.cpp
  FuzzerIO.cpp
  FuzzerIOPosix.cpp
  FuzzerIOWindows.cpp
  FuzzerLoop.cpp
  FuzzerMerge.cpp
  FuzzerMutate.cpp
  FuzzerSHA1.cpp
  FuzzerTracePC.cpp
  FuzzerUtil.cpp
  FuzzerUtilDarwin.cpp
  FuzzerUtilFuchsia.cpp
  FuzzerUtilLinux.cpp
  FuzzerUtilPosix.cpp
  FuzzerUtilWindows.cpp)

add_library(Fuzzer STATIC ${LIBFUZZER_SOURCES})




