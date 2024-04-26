cmake_minimum_required(VERSION 3.28.1)
set(CMAKE_OSX_DEPLOYMENT_TARGET 11)
project(
        VulkanTutorialRendererStarterPack
        VERSION 0.1.0.0
        LANGUAGES C CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

include(FetchContent)

FetchContent_Declare(
        glm
        URL https://github.com/g-truc/glm/archive/refs/tags/1.0.1.zip
)
FetchContent_Declare(
        SDL3
        URL https://github.com/libsdl-org/SDL/releases/download/prerelease-3.1.0/SDL3-3.1.0.tar.xz
)
FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb
)
FetchContent_Declare(
        tinyobjloader
        GIT_REPOSITORY https://github.com/tinyobjloader/tinyobjloader
        GIT_TAG release
)

FetchContent_MakeAvailable(
        glm
        SDL3
        stb
        tinyobjloader
)

find_package(Vulkan REQUIRED)

set(SHADERS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shaders)
set(SHADERS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SHADERS_BINARY_DIR})
file(GLOB_RECURSE SHADER_SOURCES ${SHADERS_SOURCE_DIR}/*.frag ${SHADERS_SOURCE_DIR}/*.vert)
foreach (SHADER_SOURCE ${SHADER_SOURCES})
    file(RELATIVE_PATH SHADER_SOURCE_RELATIVE_PATH ${SHADERS_SOURCE_DIR} ${SHADER_SOURCE})
    set(SHADER_BINARY ${SHADERS_BINARY_DIR}/${SHADER_SOURCE_RELATIVE_PATH}.spv)
    file(RELATIVE_PATH SHADER_BINARY_RELATIVE_PATH ${SHADERS_BINARY_DIR} ${SHADER_BINARY})
    add_custom_command(OUTPUT ${SHADER_BINARY}
            COMMAND ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE} -V ${SHADER_SOURCE} -o ${SHADER_BINARY}
            MAIN_DEPENDENCY ${SHADER_SOURCE}
            VERBATIM
    )
    list(APPEND SHADER_BINARIES ${SHADER_BINARY})
endforeach ()
add_custom_target(
        BUILD_SHADERS
        ALL
        DEPENDS ${SHADER_BINARIES}
)

add_executable(${PROJECT_NAME})

set(SOURCES
        src/application/application.cpp
        src/renderer/renderer.cpp
        src/window/window.cpp
)

target_include_directories(${PROJECT_NAME}
        PRIVATE
        src/application
        src/renderer
        src/window
        ${stb_SOURCE_DIR}
)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        glm::glm
        SDL3::SDL3
        tinyobjloader
        Vulkan::Vulkan
)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})
