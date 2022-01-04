cmake_minimum_required(VERSION 3.21)
project(thelabyrinth)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(glfw-3.3.6)
include_directories(glfw-3.3.6/include)


find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
set(OpenGlLinkers -lglfw3 -lglut -lGLU -lGL) # setting all the Glut libraries as one variable.

option(BUILD_SHARED_LIBS "Build shared libraries" ON)

add_executable(thelabyrinth main.cpp Renderer.h Renderer.cpp App.h App.cpp Constants.h Frustum.h ShadersManager.h StandardHeaders.h ShadersManager.cpp Camera.h Camera.cpp Shapes.h Libraries.h IOManager.h IOManager.cpp Mesh.h)
target_link_libraries(thelabyrinth glfw OpenGL::GL ${OPENGL_glu_LIBRARY} ${GLEW_LIBRARIES} ${GLM_LIBRARIES} ${GLFW_LIBRARIES})