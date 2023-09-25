# SparseArray
add_executable(SparseArrayTest SparseArray.cpp)
target_include_directories(SparseArrayTest PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(SparseArrayTest PRIVATE
    GTest::GTest
)
add_test(SparseArrayTest SparseArrayTest)

# Registry
add_executable(RegistryTest Registry.cpp)
target_include_directories(RegistryTest PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(RegistryTest PRIVATE
    GTest::GTest
    ECS
)
add_test(RegistryTest RegistryTest)

add_subdirectory(zipper)