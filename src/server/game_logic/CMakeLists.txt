set(INCROOT ${CMAKE_SOURCE_DIR}/includes/server/game_logic)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameLogic.cpp
)
add_library(GameLogic STATIC ${SRC})
target_include_directories(GameLogic PUBLIC ${INCROOT})
