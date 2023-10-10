cmake_minimum_required(VERSION 3.0.0)
project(OLAS VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 17)

find_library(COREVIDEO CoreVideo)
find_library(OPENGL OpenGL)
find_library(IOKIT IOKit)
find_library(COCOA Cocoa)
find_library(CARBON Carbon)

file(GLOB BuildFiles src/*.cpp)

add_executable(OLAS 
dependencies/glad/glad.c
${BuildFiles}
)


target_include_directories(OLAS PUBLIC dependencies/glfw/include/ dependencies/glad/ dependencies/imgui/ dependencies/imgui/backends dependencies/ includes/ dependencies/glm/ dependencies/assimp/include/)
target_link_directories(OLAS PUBLIC dependencies/glfw/ dependencies/assimp/lib/)
target_link_libraries(OLAS glfw3 libassimp.dylib ${COREVIDEO} ${OPENGL} ${IOKIT} ${COCOA} ${CARBON} )
