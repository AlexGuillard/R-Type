set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/)
set(SRC
    ${SRCROOT}/ANetwork.cpp
)
add_library(ANetwork STATIC ${SRC})
target_include_directories(ANetwork PUBLIC ${INCROOT})
target_link_libraries(ANetwork PUBLIC asio)
add_subdirectory(client)
add_subdirectory(ECS)
add_subdirectory(server)
