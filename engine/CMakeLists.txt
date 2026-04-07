file(GLOB_RECURSE ENGINE_SOURCES
    src/*.cpp
)

add_library(simpleton_engine STATIC ${ENGINE_SOURCES})

target_include_directories(simpleton_engine
    PUBLIC
    include
)