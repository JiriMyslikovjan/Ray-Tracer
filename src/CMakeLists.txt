project(ray_tracer)

add_library(ray_tracing vec3.cpp color.cpp ray.cpp object.cpp utils.cpp camera.cpp material.cpp aabb.cpp bvh.cpp texture.cpp image.cpp)

target_include_directories(ray_tracing 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include)


target_link_libraries(ray_tracing PUBLIC stb)
#target_include_directories(ray_tracing PUBLIC ${CMAKE_ROOT}/external)