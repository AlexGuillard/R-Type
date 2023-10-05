set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/createEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events.cpp
)
add_library(GameEngine STATIC ${SRC})
target_include_directories(GameEngine PUBLIC ${INCROOT})
target_link_libraries(GameEngine PRIVATE
    systems
    ECS
)