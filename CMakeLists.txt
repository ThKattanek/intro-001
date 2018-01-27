# CMakeList.txt for Intro-001 by Thorsten Kattanek
# Berlin, 01-27-2018
#
# For Static Win32 compilation must -DSFML_STATIC_LIBRARIES=TRUE
#
################################################################

cmake_minimum_required(VERSION 2.8)

##################### PROJECT #####################

project("intro-001")
message(STATUS "Project Name: " ${PROJECT_NAME})

#################### CONFIGURE ####################

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
        message(STATUS "CMAKE_BUILD_TYPE NOT FOUND")
endif()

set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "Use static SFML librares")

if(WIN32)
    if(SFML_STATIC_LIBRARIES)
        add_definitions(-DSFML_STATIC)
    endif()
endif()

##################### SOURCES #####################

set(SOURCES
    src/main.cpp
)

################### RESOURCEN #####################

if(WIN32)
    set(WIN_RC ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME}.rc)
endif()

################### LIBRARIES #####################

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SFML
# network audio graphics window system
find_package(SFML 2 COMPONENTS system window graphics REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    set(LIBRARIES ${LIBRARIES} ${SFML_SYSTEM_LIBRARY})
    set(LIBRARIES ${LIBRARIES} ${SFML_SYSTEM_DEPENDENCIES})
    set(LIBRARIES ${LIBRARIES} ${SFML_WINDOW_LIBRARY})
    set(LIBRARIES ${LIBRARIES} ${SFML_WINDOW_DEPENDENCIES})
    set(LIBRARIES ${LIBRARIES} ${SFML_GRAPHICS_LIBRARY})
    set(LIBRARIES ${LIBRARIES} ${SFML_GRAPHICS_DEPENDENCIES})
    if(WIN32)
        if(SFML_STATIC_LIBRARIES)
            set(LIBRARIES ${LIBRARIES} -lsfml-system-s png jpeg harfbuzz z bz2 winmm)
        endif()
    endif()
else()
    message(STATUS "SFML not found!")
endif()

################### EXECUTABLE ####################

if(NOT WIN32)
    add_executable(${PROJECT_NAME} ${SOURCES})
else()
    add_executable(${PROJECT_NAME} ${SOURCES} ${WIN_RC})
endif()

target_link_libraries(${PROJECT_NAME} ${LIBRARIES})



