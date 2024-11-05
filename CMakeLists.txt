cmake_minimum_required(VERSION 3.22)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Specify the project name
project(VulkanTest)

# Add source files
set(SOURCES
    src/main.cpp
    src/application.cpp
    src/graphics_pipeline.cpp
    src/window.cpp
)

# Add header files (optional, for IDE support)
set(HEADERS
    src/application.h
    src/graphics_pipeline.h
    src/window.h
)

# Create the executable
add_executable(VulkanTest ${SOURCES} ${HEADERS})

# Link required libraries
target_link_libraries(VulkanTest
    glfw
    vulkan
    dl
    pthread
    X11
    Xxf86vm
    Xrandr
    Xi
)

# Ensure that the compiler can find headers in the src directory
target_include_directories(VulkanTest PRIVATE src)
