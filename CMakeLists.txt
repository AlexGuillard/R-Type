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

    if(NOT WIN32)
        add_compile_options(-g3)
    endif()
endif()

if(WIN32)
    macro(get_WIN32_WINNT version)
        if(CMAKE_SYSTEM_VERSION)
            set(ver ${CMAKE_SYSTEM_VERSION})
            string(REGEX MATCH "^([0-9]+).([0-9])" ver ${ver})
            string(REGEX MATCH "^([0-9]+)" verMajor ${ver})
            # Check for Windows 10, b/c we'll need to convert to hex 'A'.
            if("${verMajor}" MATCHES "10")
                set(verMajor "A")
                string(REGEX REPLACE "^([0-9]+)" ${verMajor} ver ${ver})
            endif()
            # Remove all remaining '.' characters.
            string(REPLACE "." "" ver ${ver})
            # Prepend each digit with a zero.
            string(REGEX REPLACE "([0-9A-Z])" "0\\1" ver ${ver})
            set(${version} "0x${ver}")
        endif()
    endmacro()
    get_WIN32_WINNT(ver)
    add_definitions(-D_WIN32_WINNT=${ver})
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