set(INCROOT ${CMAKE_SOURCE_DIR}/includes/ECS)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
)
add_library(ECS STATIC ${SRC})
target_include_directories(ECS PUBLIC ${INCROOT})
