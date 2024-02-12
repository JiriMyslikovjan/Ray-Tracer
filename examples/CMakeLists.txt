project(ray_tracer)

add_executable(main main.cpp)

target_link_libraries(main 
    PRIVATE
    stb 
    ray_tracing
    )