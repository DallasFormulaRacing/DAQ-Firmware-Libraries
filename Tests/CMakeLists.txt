cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # The hash-ID at the end of this URL should be updated occassionally
  URL https://github.com/google/googletest/archive/f8d7d77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  daq-unit-tests
  Src/hello_test.cc

  # PE3 ECU CAN Bus Byte Parsing Tests
  ../Sensor/ECU/PE3/frame_parsing.hpp
  ../Sensor/ECU/PE3/frame_parsing.cpp
  Src/Sensor/ECU/PE3/frame_parsing_tests.cpp

  # PE3 ECU Frame Accessibility Tests
  ../Sensor/ECU/PE3/Frames/frame_pe1.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe2.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe3.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe4.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe5.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe6.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe7.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe8.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe9.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe10.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe11.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe12.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe13.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe14.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe15.hpp
  ../Sensor/ECU/PE3/Frames/frame_pe16.hpp
  Src/Sensor/ECU/PE3/pe_frames_tests.cpp

  # Circular Queue Tests
  ../Application/circular_queue.hpp
  Src/Application/circular_queue_tests.cpp
)

# Linking with `gtest_main` instead of `gtest` allows us to bypass having
#   to write a main() function
target_link_libraries(
  daq-unit-tests
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(daq-unit-tests)
