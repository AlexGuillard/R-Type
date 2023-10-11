add_executable(CreatorTest Creator.cpp)
target_include_directories(CreatorTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(CreatorTest PRIVATE
    gtest
    gtest_main
    ECS
)
add_test(CreatorTest CreatorTest)

add_subdirectory(containers)