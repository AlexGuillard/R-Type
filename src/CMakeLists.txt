set(INCROOT ${CMAKE_SOURCE_DIR}/include/)
set(SRCROOT ${CMAKE_SOURCE_DIR}/src/)
set(SRC
    ${SRCROOT}/ANetwork.cpp
)
add_library(ANetwork STATIC ${SRC})
target_include_directories(ANetwork PUBLIC ${INCROOT})

# # add pthread (needed for boost.asio)
# set(THREADS_PREFER_PTHREAD_FLAG ON)
# find_package(Threads REQUIRED)
# target_link_libraries(ANetwork PRIVATE Threads::Threads)

# add boost.asio
set(BOOST_INCLUDE_LIBRARIES thread filesystem system asio)
set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE) # Needed to print downloading progress
FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.83.0/boost-1.83.0.7z # downloading a zip release speeds up the download
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    DOWNLOAD_NO_EXTRACT FALSE
)
FetchContent_MakeAvailable(Boost)

target_link_libraries(ANetwork PRIVATE
    Boost::filesystem
    Boost::asio
    Boost::thread
)

add_subdirectory(client)
add_subdirectory(ECS)
add_subdirectory(GameEngine)
add_subdirectory(server)
