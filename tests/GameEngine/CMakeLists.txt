add_executable(GameEngineTest GameEngine.cpp)
target_include_directories(GameEngineTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(GameEngineTest PRIVATE
    GTest::GTest
    GameEngine
    ECS
)
add_test(GameEngineTest GameEngineTest)