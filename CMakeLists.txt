cmake_minimum_required(VERSION 3.8)
project("Turbine")

set(CMAKE_CXX_STANDARD 20)
find_package(Lua51 REQUIRED)

# compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("extern/")
include_directories("extern/glm")
include_directories("engine/")

option(BUILD_EDITOR "Build Blueprint alongside Turbine" OFF)

if(PSP)
    set(BUILD_EDITOR OFF)
    # PIC does not work on PSP
    set(YAML_ENABLE_PIC OFF CACHE BOOL "PIC" FORCE)
endif()

add_subdirectory("extern/yaml-cpp/")
add_subdirectory("extern/entt/")
if(!PSP)
add_subdirectory("extern/glfw/")
find_package(glm CONFIG REQUIRED)
endif()

# Common engine code, compiled on all platforms
file(GLOB COMMON_SRC
    "engine/*.cpp"
    "engine/scene/*.cpp"
    "engine/components/*.cpp"
    "engine/systems/*.cpp"
    "engine/renderer/*.cpp"
    "engine/platform/*.cpp"
    "engine/math/*.cpp"
)

if(UNIX)
    file(GLOB UNIX_SRC
        "engine/platform/linux-bsd/*.cpp"
        "engine/renderer/opengl/*.cpp"
        "engine/glad.c"
    )
    list(APPEND COMMON_SRC ${UNIX_SRC})

    # Build Blueprint if enabled.
    if(BUILD_EDITOR)
        include_directories("extern/imgui/")
        include_directories("engine/")
        file(GLOB EDITOR_SRC
            "extern/imgui/*.cpp"
            "extern/imgui/backends/imgui_impl_glfw.cpp"
            "extern/imgui/backends/imgui_impl_opengl3.cpp"
            "editor/*.cpp"
        )
        list(APPEND COMMON_SRC ${EDITOR_SRC})
    endif()

    add_executable(${PROJECT_NAME} ${COMMON_SRC})
    target_link_libraries(${PROJECT_NAME}
        glfw
        lua
        yaml-cpp::yaml-cpp
        EnTT::EnTT
    )
endif()

if(PSP)
    list(REMOVE_ITEM COMMON_SRC
      ${CMAKE_CURRENT_SOURCE_DIR}/engine/renderer/shader.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/engine/renderer/varray.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/engine/renderer/vbuffer.cpp
    )
    file(GLOB PSP_SRC
        "engine/platform/psp/*.cpp"
        "engine/renderer/gu/*.cpp"
    )
    list(APPEND COMMON_SRC ${PSP_SRC})
    add_executable(${PROJECT_NAME} ${COMMON_SRC})
    target_link_libraries(${PROJECT_NAME}
        EnTT::EnTT
        yaml-cpp::yaml-cpp
        GL
        lua
        pspvram
        pspaudio
        pspvfpu
        pspdisplay
        pspgum
        pspgu
        pspge
        pspdebug
        psphprm
        pspctrl
    )
    create_pbp_file(
        TARGET ${PROJECT_NAME}
        ICON_PATH NULL
        BACKGROUND_PATH NULL
        PREVIEW_PATH NULL
        TITLE ${PROJECT_NAME}
	    # BUILD_PRX
    )
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sample/
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/sample/)
