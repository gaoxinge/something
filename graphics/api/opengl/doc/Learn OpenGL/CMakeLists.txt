cmake_minimum_required(VERSION 3.10)
project(LearnOpenGL)

if(MSVC)
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
add_subdirectory(external/glfw)
add_subdirectory(external/glad)
add_executable(main WIN32 main.cpp)
target_link_libraries(main ${OPENGL_LIBRARIES} glfw glad)
