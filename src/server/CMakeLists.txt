add_executable(r-type_server main.cpp)
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
install(TARGETS r-type_server RUNTIME DESTINATION bin)
target_link_libraries(r-type_server PUBLIC ServerNetwork GameEngineServer)

add_subdirectory(game_logic)
add_subdirectory(network)
