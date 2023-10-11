set(INCROOT ${CMAKE_SOURCE_DIR}/include)
set(SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Creator.cpp
)
add_library(ECS STATIC ${SRC})
target_include_directories(ECS PUBLIC ${INCROOT})
target_link_libraries(ECS PUBLIC assets)

add_subdirectory(systems)