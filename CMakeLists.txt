cmake_minimum_required(VERSION 3.22)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the project name
project(GeckoEngine)

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add source files
set(SOURCES
    src/main.cpp
    src/application.cpp
    src/device.cpp
    src/graphics_pipeline.cpp
    src/model.cpp
    src/object.cpp
    src/renderer.cpp
    src/swap_chain.cpp
    src/window.cpp
)

# Add header files (optional, for IDE support)
set(HEADERS
    src/application.h
    src/device.h
    src/graphics_pipeline.h
    src/model.h
    src/object.h
    src/renderer.h
    src/swap_chain.h
    src/window.h
)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

# Set the C++ standard explicitly
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -std=c++17)

# Link required libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
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
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)
