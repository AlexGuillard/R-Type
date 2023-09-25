set(INCROOT ${PROJECT_SOURCE_DIR}/includes)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteSheetDrawer.cpp
)
add_library(systems_helper STATIC ${SRC})
target_include_directories(systems_helper PUBLIC ${INCROOT})
target_link_libraries(systems_helper PRIVATE
    raylib
)