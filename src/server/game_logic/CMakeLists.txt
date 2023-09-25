set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameLogic.cpp
)
add_library(GameLogic STATIC ${SRC})
target_include_directories(GameLogic PUBLIC ${INCROOT})
