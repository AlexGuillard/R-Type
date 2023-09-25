set(INCROOT ${CMAKE_SOURCE_DIR}/includes)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Display.cpp
)
add_library(Display STATIC ${SRC})
target_include_directories(Display PUBLIC ${INCROOT})
