add_executable(r-type_client main.cpp)
set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_subdirectory(display)
add_subdirectory(network)
