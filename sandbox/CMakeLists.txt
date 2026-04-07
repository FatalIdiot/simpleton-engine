file(GLOB_RECURSE SANDBOX_SOURCES
    src/*.cpp
)

add_executable(sandbox ${SANDBOX_SOURCES})

target_link_libraries(sandbox
    simpleton_engine
)