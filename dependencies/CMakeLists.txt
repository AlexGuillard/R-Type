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

# on linux
if(UNIX AND NOT APPLE)
	# get linux distro
	execute_process(COMMAND lsb_release -si OUTPUT_VARIABLE LINUX_DISTRO)
	string(STRIP ${LINUX_DISTRO} LINUX_DISTRO)

	# on ubuntu
	if(${LINUX_DISTRO} STREQUAL "Ubuntu")
		# install boost
		execute_process(COMMAND sudo apt-get -y install libboost-all-dev)

		# install gtest
		execute_process(COMMAND sudo apt-get -y install libgtest-dev googletest)

	# on debian
	elseif(${LINUX_DISTRO} STREQUAL "Debian")
		# install boost
		execute_process(COMMAND sudo apt-get -y install libboost-all-dev)

		# install gtest
		execute_process(COMMAND sudo apt-get -y install libgtest-dev googletest)

	# on fedora
	elseif(${LINUX_DISTRO} STREQUAL "Fedora")
		# install boost
		execute_process(COMMAND sudo dnf -y install boost-devel)

		# install gtest
		execute_process(COMMAND sudo dnf -y install gtest-devel)

	# on arch
	elseif(${LINUX_DISTRO} STREQUAL "Arch")
		# install boost
		execute_process(COMMAND sudo pacman -S boost --noconfirm)

		# install gtest
		execute_process(COMMAND sudo pacman -S gtest --noconfirm)
	endif()

# on windows
elseif(WIN32)
	# install boost
	execute_process(COMMAND choco install boost-msvc-14.1 --yes)

	# install gtest
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG v1.14.0
	)
	FetchContent_MakeAvailable(googletest)

# on macos
elseif(APPLE)
	# install boost
	execute_process(COMMAND yes | brew install boost)

	# install gtest
	execute_process(COMMAND yes | brew install googletest)
endif()
