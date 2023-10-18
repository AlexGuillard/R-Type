set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientNetwork.cpp
    ${CMAKE_SOURCE_DIR}/src/server/network/sendCode.cpp
    ${CMAKE_SOURCE_DIR}/src/ECS/Creator.cpp

)
add_library(ClientNetwork STATIC ${SRC})
target_link_libraries(ClientNetwork PUBLIC ANetwork Boost::asio)
target_include_directories(ClientNetwork PUBLIC ${INCROOT})
# add the -g flag
target_compile_options(ClientNetwork PUBLIC -g3)