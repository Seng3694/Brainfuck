cmake_minimum_required(VERSION 2.4)

project(brainfuck)

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
 	set(ENV "ENV_64")
else() 
	set(ENV "ENV_86")
endif() 

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(HEADERS
	include/Node.h
	include/Stack.h
)

set(SOURCES
	src/Main.c
	src/Node.c
	src/Stack.c
)

include_directories(include)
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${ENV})
