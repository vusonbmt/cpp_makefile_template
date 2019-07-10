cmake_minimum_required (VERSION 3.5)

set(TARGET socket_multithreading)

set(PROJ_PATH ${CMAKE_SOURCE_DIR})

project({TARGET})

include_directories(${PROJ_PATH}/debug/inc)
include_directories(${PROJ_PATH}/socket/inc)
include_directories(${PROJ_PATH}/thread/inc)
include_directories(${PROJ_PATH}/mutex/inc)
include_directories(${PROJ_PATH}/tinyxml/inc)

set(EXECUTABLE_OUTPUT_PATH ${PROJ_PATH}/bin)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")

set(SOURCE
	${PROJ_PATH}/debug/src/Debug.cpp
	${PROJ_PATH}/socket/src/Socket.cpp
	${PROJ_PATH}/thread/src/Thread.cpp
	${PROJ_PATH}/mutex/src/Mutex.cpp
	${PROJ_PATH}/tinyxml/src/tinyxml2.cpp
	${PROJ_PATH}/main.cpp
)

add_executable(${TARGET} ${SOURCE})

target_link_libraries(${TARGET} pthread)
