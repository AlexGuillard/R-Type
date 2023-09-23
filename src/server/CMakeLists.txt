add_executable(r-type_server main.cpp)
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
add_subdirectory(game_logic)
add_subdirectory(network)
