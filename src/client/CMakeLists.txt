set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/network.cpp
)
add_library(ClientNetworkInterface STATIC ${SRC})
target_link_libraries(ClientNetworkInterface PUBLIC ClientNetwork Boost::asio)
target_include_directories(ClientNetworkInterface PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(r-type_client main.cpp "r-type_client.cpp")
set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
target_link_libraries(r-type_client PRIVATE
    GameEngineClient
    ClientNetworkInterface
    Display
)
target_include_directories(r-type_client PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
install(TARGETS r-type_client RUNTIME DESTINATION bin)

add_subdirectory(display)
add_subdirectory(network)
add_subdirectory(audio)