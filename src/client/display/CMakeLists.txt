set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Display.cpp
)
add_library(Display STATIC ${SRC})
target_include_directories(Display PUBLIC ${INCROOT})
target_link_libraries(Display PUBLIC
    raylib
)
