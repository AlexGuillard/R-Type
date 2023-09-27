find_package(GTest REQUIRED) # Find the googletest library

if(NOT TARGET GTest::GTest) # Prevent overriding the parent project's compiler/linker
    add_library(GTest::GTest INTERFACE IMPORTED)
else() # If the target already exists, just make sure it's imported
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

target_link_libraries(GTest::GTest INTERFACE gtest_main)

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