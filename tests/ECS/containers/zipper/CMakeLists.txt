# SparseArray
add_executable(ZipperTest Zipper.cpp IndexedZipper.cpp)
target_include_directories(ZipperTest PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(ZipperTest PRIVATE
    gtest
    gtest_main
)
add_test(ZipperTest ZipperTest)
