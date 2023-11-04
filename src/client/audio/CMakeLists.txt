set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/GameAudio.cpp
)
add_library(Audio STATIC ${SRC})
target_include_directories(Audio PUBLIC ${INCROOT})
target_link_libraries(Audio PUBLIC
    raylib
    assets
)
