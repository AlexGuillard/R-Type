set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/ServerNetwork.cpp
)
add_library(ServerNetwork STATIC ${SRC})
target_link_libraries(ServerNetwork PUBLIC ANetwork)
target_include_directories(ServerNetwork PUBLIC ${INCROOT})
