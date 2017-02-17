cmake_minimum_required(VERSION 2.8)


set(LIBRARIES_DIR ${CMAKE_SOURCE_DIR}/lib/)
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/sources/)

file( GLOB SOURCES "${SOURCE_DIR}/*.cpp"
		   "${SOURCE_DIR}/*.hpp")

set( CMAKE_CXX_FLAGS "-std=c++17" )

add_executable( run ${SOURCES} )

TARGET_LINK_LIBRARIES(run ${LIBRARIES_DIR}/libglfw.so.3.2
			  ${LIBRARIES_DIR}/libGLEW.so.2.0.0
			  ${LIBRARIES_DIR}/libGLU.so.1.3.1
			  ${LIBRARIES_DIR}/libGL.so.1)
