set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/SpriteSheetDrawer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/BackgroundDrawer.cpp
)
add_library(systems_helper STATIC ${SRC})
target_include_directories(systems_helper PUBLIC ${INCROOT})
target_link_libraries(systems_helper PRIVATE
    raylib
)