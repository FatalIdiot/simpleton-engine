file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
    ../vendor/glad/src/glad.c
)

add_library(simpleton_engine STATIC ${ENGINE_SOURCES})

target_include_directories(simpleton_engine
    PUBLIC
    include
    ../vendor/glad/include
)


include(FetchContent)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8
)

FetchContent_MakeAvailable(glfw)


include(FetchContent)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG master  
)

FetchContent_MakeAvailable(glm)

target_link_libraries(simpleton_engine PRIVATE glfw glm)