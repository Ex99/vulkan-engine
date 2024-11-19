cmake_minimum_required(VERSION 3.22)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the project name
project(GeckoEngine
    VERSION 0.1.0
    DESCRIPTION "A Vulkan rendering engine"
    LANGUAGES CXX
)

# Find required packages
find_package(VulkanLoader            REQUIRED)
find_package(vulkan-validationlayers REQUIRED)
find_package(glfw3                   REQUIRED)
find_package(glm                     REQUIRED)
find_package(tinyobjloader           REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/application.cpp
    src/camera.cpp
    src/device.cpp
    src/graphics_pipeline.cpp
    src/input.cpp
    src/model.cpp
    src/object.cpp
    src/renderer.cpp
    src/rendering_server.cpp
    src/swap_chain.cpp
    src/window.cpp
)

# Add header files (optional, for IDE support)
set(HEADERS
    src/application.h
    src/camera.h
    src/device.h
    src/graphics_pipeline.h
    src/input.h
    src/model.h
    src/object.h
    src/renderer.h
    src/rendering_server.h
    src/swap_chain.h
    src/window.h
)

# Create the executable
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# Link required libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    Vulkan::Loader
    vulkan-validationlayers::vulkan-validationlayers
    glfw
    glm::glm
    tinyobjloader::tinyobjloader)

# Find glslangValidator
find_program(GLSLANG_VALIDATOR glslangValidator)

if(GLSLANG_VALIDATOR)
    # Compile shaders
    set(SHADER_DIR "${CMAKE_SOURCE_DIR}/shaders")
    set(SPIRV_DIR "${CMAKE_BINARY_DIR}/shaders")

    file(MAKE_DIRECTORY ${SPIRV_DIR})
    file(GLOB SHADERS "${SHADER_DIR}/*.vert" "${SHADER_DIR}/*.frag")

    foreach(SHADER ${SHADERS})
        get_filename_component(FILE_NAME ${SHADER} NAME)
        set(SPIRV "${SPIRV_DIR}/${FILE_NAME}.spv")
        add_custom_command(
            OUTPUT ${SPIRV}
            COMMAND ${GLSLANG_VALIDATOR} -V ${SHADER} -o ${SPIRV}
            DEPENDS ${SHADER}
        )
        list(APPEND SPIRV_SHADERS ${SPIRV})
    endforeach(SHADER ${SHADERS})

    add_custom_target(compile_shaders ALL DEPENDS ${SPIRV_SHADERS})
    add_dependencies(${CMAKE_PROJECT_NAME} compile_shaders)
else()
    message(WARNING "Shader compiler not found. Make sure to install it and compile the shaders manually.")
endif()
