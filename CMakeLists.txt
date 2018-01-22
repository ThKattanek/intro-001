cmake_minimum_required(VERSION 3.1)

# Wenn CMAKE_BUILD_TYPE nicht gesetzt wurde auf Release setzen
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
	message(STATUS "CMAKE_BUILD_TYPE NOT FOUND")
endif()

set(PROJECT_NAME "intro-001")
project(${PROJECT_NAME})

# Configuration options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

# General compiler options
if (SFML_STATIC_LIBRARIES)
	add_definitions(-DSFML_STATIC)
endif()

# Specific compiler options

if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -stdlib=libc++")
endif()

set (CMAKE_CXX_STANDARD 11)

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
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_DEPENDENCIES})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()
