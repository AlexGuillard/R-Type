set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameEngine.cpp
)
add_library(GameEngine STATIC ${SRC})
target_include_directories(GameEngine PUBLIC ${INCROOT})
