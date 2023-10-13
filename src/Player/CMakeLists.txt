# Client
set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/utils.cpp
)
add_library(player STATIC ${SRC})
target_include_directories(player PUBLIC ${INCROOT})
