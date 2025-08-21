cmake_minimum_required(VERSION 3.16)
project(OpenGLExamples VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG        3.3.8
)
FetchContent_MakeAvailable(glfw)

# GLAD
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG        v0.1.36
)
FetchContent_MakeAvailable(glad)

# OpenGL
find_package(OpenGL REQUIRED)

# GLUT
if(WIN32)
    # No Windows, o GLUT é geralmente freeglut
else()
    find_package(GLUT REQUIRED)
endif()

# ====== Executáveis ======
# main.cpp (GLFW + GLAD)
add_executable(main_example src/main.cpp)
target_link_libraries(main_example PRIVATE glfw glad)
if(WIN32)
  target_link_libraries(main_example PRIVATE opengl32)
else()
  target_link_libraries(main_example PRIVATE OpenGL::GL)
endif()

# cood_0_1.cpp (GLUT)
add_executable(cood_0_1 src/cood_0_1.cpp)
if(WIN32)
  target_link_libraries(cood_0_1 PRIVATE opengl32 glu32 freeglut)
else()
  target_link_libraries(cood_0_1 PRIVATE OpenGL::GL GLUT::GLUT)
endif()

# cood_m1_1.cpp (GLUT)
add_executable(cood_m1_1 src/cood_m1_1.cpp)
if(WIN32)
  target_link_libraries(cood_m1_1 PRIVATE opengl32 glu32 freeglut)
else()
  target_link_libraries(cood_m1_1 PRIVATE OpenGL::GL GLUT::GLUT)
endif()
