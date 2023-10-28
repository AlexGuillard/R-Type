set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/sendCode.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Participants.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerTcp.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerNetwork.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/recupInfos.cpp
)
add_library(ServerNetwork STATIC ${SRC})
target_include_directories(ServerNetwork PUBLIC ${INCROOT})
target_link_libraries(ServerNetwork PUBLIC
    ANetwork
    Boost::asio
    assets
)
