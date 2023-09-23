# raylib dependency
set(RAYLIB_VERSION 4.5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if(NOT raylib_FOUND) # If there's none, fetch and build raylib
    message(STATUS "raylib package not found. Fetching raylib ${RAYLIB_VERSION} from source...")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)

    if(NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
else()
    message(STATUS "Found raylib ${RAYLIB_VERSION} in system.")
endif()

# gtest dependency
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# asio dependency
# Force the script to use FetchContent and not CPM internally to fetch asio
option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
option(
    ASIO_CPM_FETCHCONTENT_COMPAT
    "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
    ON
)

# Download this repository
include(FetchContent)
FetchContent_Declare(
    asiocmake
    GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
    GIT_TAG "main"
)
FetchContent_MakeAvailable(asiocmake)
