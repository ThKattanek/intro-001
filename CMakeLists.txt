cmake_minimum_required(VERSION 2.8)

# Specify default build type if none provided (before project() command)
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
	message(STATUS "CMAKE_BUILD_TYPE NOT FOUND")
endif()

# For generators with multiple configurations (like VS), only allow Debug and Release
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Limited configurations" FORCE)
	mark_as_advanced(CMAKE_CONFIGURATION_TYPES)
endif()

set(PROJECT_NAME "intro-001")
project(${PROJECT_NAME})

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

# General compiler options
if (SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
	message(STATUS "TEST")
endif()

# Specific compiler options
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
endif()

set(SOURCES src/main.cpp)

if(WIN32)
    set(WIN_RC
                ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}.rc
        )
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${PROJECT_NAME} ${SOURCES} ${WIN_RC})

if(SFML_STATIC_LIBRARIES)
		set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "SFML_STATIC")
	endif()


# SFML
# network audio graphics window system
find_package(SFML 2 COMPONENTS system window graphics)
if(SFML_FOUND)
    message(STATUS "SFML wurde gefunden.")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_DEPENDENCIES})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
