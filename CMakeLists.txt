cmake_minimum_required(VERSION 3.10)
project(RemoteAccessTool)

set(CMAKE_CXX_STANDARD 17)

# Include WebRTC headers
include_directories(third_party/webrtc/include)

# Link WebRTC libraries
link_directories(third_party/webrtc/lib)

# Create the executable
add_executable(remote_access src/main.cpp src/webrtc_module.cpp)

# Link WebRTC to the project
target_link_libraries(remote_access webrtc)