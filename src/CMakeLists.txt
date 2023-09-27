set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/)
set(SRC
    ${SRCROOT}/ANetwork.cpp
)
add_library(ANetwork STATIC ${SRC})
target_include_directories(ANetwork PUBLIC ${INCROOT})

# add pthread (needed for boost.asio)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(ANetwork PRIVATE Threads::Threads)

# add boost.asio
find_package(Boost REQUIRED COMPONENTS system)
target_include_directories(ANetwork PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(ANetwork PRIVATE ${Boost_LIBRARIES})

add_subdirectory(client)
add_subdirectory(ECS)
add_subdirectory(GameEngine)
add_subdirectory(server)
