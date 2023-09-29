# raylib dependency
set(RAYLIB_VERSION 4.5.0)
message(STATUS "Fetching raylib ${RAYLIB_VERSION} from source...")
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
include(FetchContent)
FetchContent_MakeAvailable(raylib)

# install gtest
message(STATUS "Fetching googletest from source...")
include(FetchContent)
FetchContent_Declare(
	googletest
	DOWNLOAD_EXTRACT_TIMESTAMP OFF
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_GetProperties(googletest)

if(NOT googletest_POPULATED)
	set(FETCHCONTENT_QUIET NO)
	FetchContent_Populate(googletest)
	set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
FetchContent_MakeAvailable(googletest)

# set(BOOST_INCLUDE_LIBRARIES thread filesystem system asio)
# set(BOOST_ENABLE_CMAKE ON)

# message(STATUS "Fetching Boost from source...")
# include(FetchContent)
# FetchContent_Declare(
#     Boost
#     DOWNLOAD_EXTRACT_TIMESTAMP OFF
#     URL URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.tar.gz
# )
# FetchContent_GetProperties(Boost)

# if(NOT Boost_POPULATED)
#     set(FETCHCONTENT_QUIET NO)
#     FetchContent_Populate(Boost)
# 	set(BOOST_ROOT ${CMAKE_BINARY_DIR}/boost-prefix)
#     set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build the supplied examples
# endif()
# FetchContent_MakeAvailable(Boost)

# # on windows
# elseif(WIN32)
# 	# install boost
# 	execute_process(COMMAND choco install boost-msvc-14.1 --yes)
# endif()
