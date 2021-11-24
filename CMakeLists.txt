cmake_minimum_required(VERSION 3.14)
project(space_invaders)

set(CMAKE_CXX_STANDARD 11)
find_package(glfw3 3.2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)


add_executable(space_invaders
    main.cpp)

target_link_libraries(space_invaders glfw)
target_link_libraries(space_invaders OpenGL::GL)
target_link_libraries(space_invaders GLEW::GLEW)
 