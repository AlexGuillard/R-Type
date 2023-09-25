set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/movement.cpp
)
add_library(systems STATIC ${SRC})
target_include_directories(ECS PUBLIC ${INCROOT})
target_link_libraries(systems PUBLIC
    raylib
    systems_helper
)

add_subdirectory(helper)