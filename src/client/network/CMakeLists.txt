set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ClientNetwork.cpp
    ${CMAKE_SOURCE_DIR}/src/server/network/sendCode.cpp
)
add_library(ClientNetwork STATIC ${SRC})
target_link_libraries(ClientNetwork PUBLIC ANetwork Boost::asio ECS)
target_include_directories(ClientNetwork PUBLIC ${INCROOT})