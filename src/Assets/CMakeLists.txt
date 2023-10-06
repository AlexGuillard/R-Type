# get all game assets pathes
file(GLOB_RECURSE ASSETS
    ${PROJECT_SOURCE_DIR}/assets/game/*
)

# set variables
string(REGEX REPLACE "/src/" "/include/" CURRENT_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ASSET_HEADER ${CURRENT_HEADER_DIR}/generatedAssets.hpp)
set(ASSET_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/generatedAssets.cpp)
set(ASSET_INPUT_DIR ${CMAKE_SOURCE_DIR}/assets/game)

# create custom cmake target that converts assets to cpp/hpp files
add_custom_command(
    COMMENT "Converting game assets to C file"
    OUTPUT ${ASSET_SOURCE} ${ASSET_HEADER}
    COMMAND ${CMAKE_COMMAND} -D INPUT_DIR=${ASSET_INPUT_DIR} -D OUTPUT_HEADER=${ASSET_HEADER} -D OUTPUT=${ASSET_SOURCE} -P create_ressources.cmake
    DEPENDS ${ASSETS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# create library
set(SOURCES ${ASSET_SOURCE} AssetLoader.cpp)
add_library(assets STATIC ${SOURCES})
target_include_directories(assets PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(assets PRIVATE raylib)
