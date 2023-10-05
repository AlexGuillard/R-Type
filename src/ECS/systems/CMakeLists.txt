set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/movement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/invincibleTimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gravity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shooting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/collision.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sinMovement.cpp
)
add_library(systems STATIC ${SRC})
target_include_directories(ECS PUBLIC ${INCROOT})
target_link_libraries(systems PUBLIC
    raylib
    systems_helper
    GameEngine
)

add_subdirectory(helper)