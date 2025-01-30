cmake_minimum_required(VERSION 3.10)
project(RemoteAccessTool)

set(CMAKE_CXX_STANDARD 17)

# Include DirectX Headers
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(remote_access src/main.cpp src/screen_capture.cpp)

# Link DirectX Libraries
target_link_libraries(remote_access d3d11 dxgi)