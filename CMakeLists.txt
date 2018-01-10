cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME "intro-001")
project(${PROJECT_NAME})

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
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

# SFML
# network audio graphics window system
find_package(SFML 2 REQUIRED system window graphics)
if(SFML_FOUND)
    message(STATUS "SFML wurde gefunden.")
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()
