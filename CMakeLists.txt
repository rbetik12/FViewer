cmake_minimum_required (VERSION 3.8)

project ("FViewer")
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(Src/Viewer)
add_subdirectory(Lib/glad)
add_subdirectory(Lib/glfw)
add_subdirectory(Lib/glm/glm)
add_subdirectory(Lib/imgui)