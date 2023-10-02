cmake_minimum_required(VERSION 3.24.0)
enable_testing()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

project(R-Type VERSION 0.0.1 LANGUAGES CXX DESCRIPTION "RType")
set(CMAKE_CXX_STANDARD 20)

# add -DDEBUG and -g3 to compiler flags in debug mode
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG)
    add_compile_options(-g3)
endif()

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