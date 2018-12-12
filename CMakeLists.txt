cmake_minimum_required (VERSION 2.6)
project (nottriangless)



# include KHR and glad extension loader
include_directories("${PROJECT_SOURCE_DIR}/src/glad/include")
add_subdirectory (src/glad)
set (EXTRA_LIBS ${EXTRA_LIBS} glad)


# add glfw loader
include_directories("${PROJECT_SOURCE_DIR}/src/glfw-3.2.1/include")
add_subdirectory (src/glfw-3.2.1)
set (EXTRA_LIBS ${EXTRA_LIBS} glfw)


# add engine 
include_directories("${PROJECT_SOURCE_DIR}/src/engine/include")
add_subdirectory (src/engine)
set (EXTRA_LIBS ${EXTRA_LIBS} engine)


set (TRIANGLES_VERSION_MAJOR 1)
set (TRIANGLES_VERSION_MINOR 0)

add_executable(triangles src/triangles-src/main.cpp)

target_link_libraries (triangles ${EXTRA_LIBS})