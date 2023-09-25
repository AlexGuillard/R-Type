# SparseArray
add_executable(ZipperTest Zipper.cpp IndexedZipper.cpp)
target_include_directories(ZipperTest PRIVATE ${CMAKE_SOURCE_DIR}/includes)
target_link_libraries(ZipperTest PRIVATE GTest::GTest
)
add_test(ZipperTest ZipperTest)
