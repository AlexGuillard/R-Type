cmake_minimum_required(VERSION 3.27.4)
enable_testing()
set(CMAKE_BUILD_TYPE Release)
project(R-Type VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "RType")
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(dependencies)
add_subdirectory(src)
add_subdirectory(tests)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_SOURCE_DIR}/LICENSE)
set(CPACK_PACKAGE_VERSION_MAJOR ${R-Type_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${R-Type_VERSION_MINOR})
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

# install assets
install(DIRECTORY assets DESTINATION .)