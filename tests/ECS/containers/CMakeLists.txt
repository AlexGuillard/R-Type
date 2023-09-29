# SparseArray
add_executable(SparseArrayTest SparseArray.cpp)
target_include_directories(SparseArrayTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(SparseArrayTest PRIVATE
    gtest
    gtest_main
)
add_test(SparseArrayTest SparseArrayTest)

# Registry
add_executable(RegistryTest Registry.cpp)
target_include_directories(RegistryTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(RegistryTest PRIVATE
    gtest
    gtest_main
    ECS
)
add_test(RegistryTest RegistryTest)

add_subdirectory(zipper)