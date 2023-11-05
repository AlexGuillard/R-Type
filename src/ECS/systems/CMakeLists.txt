set(INCROOT ${PROJECT_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/drawable.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/movement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/invincibleTimer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/gravity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/shooting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/collision.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/damage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sinMovement.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/target.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/walkingAI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/solid.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/background.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ground.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/horizontalScroll.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bydoShootingAI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/findTarget.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/flyingAI.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/bossIntro.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/pickup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/adaptiveFlyingAI.cpp
)
add_library(systems STATIC ${SRC})
target_include_directories(ECS PUBLIC ${INCROOT})
target_link_libraries(systems PUBLIC
    raylib
    systems_helper
    GameEngine
    assets
    player
    Display
)

add_subdirectory(helper)