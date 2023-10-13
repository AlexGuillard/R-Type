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

# Client
set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/createClientEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events.cpp
)
add_library(GameEngineClient STATIC ${SRC})
target_include_directories(GameEngineClient PUBLIC ${INCROOT})
target_link_libraries(GameEngineClient PRIVATE
    systems
    ECS
    GameEngine
)

# Server
set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/createServerEngine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Events.cpp
)
add_library(GameEngineServer STATIC ${SRC})
target_include_directories(GameEngineServer PUBLIC ${INCROOT})
target_link_libraries(GameEngineServer PRIVATE
    systems
    ECS
    GameEngine
)