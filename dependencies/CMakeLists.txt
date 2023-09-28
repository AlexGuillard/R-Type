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
	if(EXISTS "/etc/os-release")
		file(STRINGS "/etc/os-release" OS_RELEASE_CONTENTS)

		foreach(line ${OS_RELEASE_CONTENTS})
			if(line MATCHES "^ID=")
				string(REGEX REPLACE "ID=(.*)" "\\1" LINUX_DISTRO "${line}")
			endif()
		endforeach()

		message("Distribution Name: ${LINUX_DISTRO}")
	endif()

	# on ubuntu
	if("${LINUX_DISTRO}" STREQUAL "ubuntu")
		# install boost
		execute_process(COMMAND sudo apt-get -y install libboost-all-dev)

		# install gtest
		execute_process(COMMAND sudo apt-get -y install libgtest-dev googletest)

	# on debian
	elseif("${LINUX_DISTRO}" STREQUAL "debian")
		# install boost
		execute_process(COMMAND sudo apt-get -y install libboost-all-dev)

		# install gtest
		execute_process(COMMAND sudo apt-get -y install libgtest-dev googletest)

	# on fedora
	elseif("${LINUX_DISTRO}" STREQUAL "fedora")
		# install boost
		execute_process(COMMAND sudo dnf -y install boost-devel)

		# install gtest
		execute_process(COMMAND sudo dnf -y install gtest-devel)

	# on arch
	elseif("${LINUX_DISTRO}" STREQUAL "arch")
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
		URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
	)
	# For Windows: Prevent overriding the parent project's compiler/linker settings
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
	FetchContent_MakeAvailable(googletest)
	set_target_properties(gtest PROPERTIES
		IMPORTED_LOCATION ${binary_dir}/libgtest.a
	)
	set_target_properties(gtest_main PROPERTIES
		IMPORTED_LOCATION ${binary_dir}/libgtest_main.a
	)
# on macos
elseif(APPLE)
	# install boost
	execute_process(COMMAND yes | brew install boost)

	# install gtest
	execute_process(COMMAND yes | brew install googletest)
endif()
