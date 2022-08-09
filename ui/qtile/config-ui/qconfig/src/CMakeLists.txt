## /src/CMakeLists

add_executable(qconfig main.cpp)
target_include_directories(qconfig PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(qconfig PRIVATE project_options)
