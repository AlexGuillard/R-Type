# Copy the lines below to add unit tests. Replace text that looks like this:
# [REPLACE] with the appropriate values.
# [TEXT]... means that the text can be reapeted as many times as needed.
# [TEXT]? means that the text is optional.

# add_executable([TEST_NAME] [FILE1.CPP]...)
# target_include_directories([TEST_NAME] PRIVATE ${CMAKE_SOURCE_DIR}/include)
# target_link_libraries([TEST_NAME] PRIVATE GTest::GTest
# [LIBRARY1]?...
# )
# add_test([TEST_NAME] [TEST_NAME])
add_subdirectory(ECS)
add_subdirectory(GameEngine)