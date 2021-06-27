cmake_minimum_required (VERSION 3.8)

include_directories(../Parser/include)
include_directories(../../Lib/glad/include)
include_directories(../../Lib/glfw/include)
include_directories(../../Lib/glm)
add_executable(${PROJECT_NAME} main.cpp
        Deserialize/Deserializer.cpp
        Deserialize/Deserializer.h
        Util/timer.hpp Renderer/Renderer.cpp Renderer/Renderer.h
        Renderer/IndexBuffer.h Renderer/IndexBuffer.cpp
        Renderer/VertexArray.h Renderer/VertexArray.cpp
        Renderer/VertexBuffer.h Renderer/VertexBuffer.cpp
        Renderer/VertexBufferLayout.h Renderer/VertexBufferLayout.cpp
        Renderer/VertexBufferElement.cpp
        Renderer/Window.h Renderer/Window.cpp
        Renderer/Shader.h Renderer/Shader.cpp
        ../Debug/Debug.cpp ../Debug/Debug.h Renderer/Light.cpp Renderer/Light.h Input/Input.cpp Input/Input.h)

target_link_libraries(${PROJECT_NAME} glad glfw)

