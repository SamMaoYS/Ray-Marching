cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
if(POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

project(sdf)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)
find_package (Eigen3 REQUIRED)

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    link_libraries(${GLEW_LIBRARIES})
endif()

include_directories(SYSTEM includes)
include_directories(${EIGEN3_INCLUDE_DIRS})

file(GLOB resources "includes/*.h" "src/*.cpp")

add_executable (main ${resources})
target_link_libraries (main OpenGL::GL Eigen3::Eigen glfw)
