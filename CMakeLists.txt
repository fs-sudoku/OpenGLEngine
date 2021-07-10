cmake_minimum_required (VERSION 3.8)

project(Application)

set(IS_DEBUG 1)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

# find all source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)
	
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/src/*.h
	${CMAKE_SOURCE_DIR}/src/*.hpp)

file(GLOB_RECURSE DLL_FILES 
	${CMAKE_SOURCE_DIR}/dlls/*.dll)

# set vars
set(INCLUDE_PATH ${CMAKE_SOURCE_DIR}/include)
set(LIBS_PATH ${CMAKE_SOURCE_DIR}/lib)

set(LIBS_NAMES SDL/SDL2 GL/glew32 GL/glut32 Lua/lua54 opengl32 glu32)

# set paths
include_directories(${INCLUDE_PATH} ${CMAKE_SOURCE_DIR}/src)
link_directories(${LIBS_PATH} ${LIBS_PATH}/SDL)

string(TIMESTAMP TODAY "\"Date: %Y.%m.%d Time: %H.%M.%S\"")

# add game executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
# add game variables
target_compile_definitions(
	${PROJECT_NAME} PRIVATE LAST_COMPILE_TIME=${TODAY} IS_EDITOR=0 IS_DEBUG=${IS_DEBUG}
)
target_link_libraries(${PROJECT_NAME} ${LIBS_NAMES})

project(Editor)

# add editor executable
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})
# add editor variables
target_compile_definitions(
	${PROJECT_NAME} PRIVATE LAST_COMPILE_TIME=${TODAY} IS_EDITOR=1 IS_DEBUG=${IS_DEBUG}
)
target_link_libraries(${PROJECT_NAME} ${LIBS_NAMES})

# copy .dlls
if (MSVC)
	file(COPY ${DLL_FILES} DESTINATION ${PROJECT_BINARY_DIR}/bin)
endif()

# macro copy gamedata directory
macro(copy_directory _proj _src _dst)
add_custom_command(TARGET ${_proj} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${_src}
        ${_dst}
	)
endmacro()

# copy gamedata directory
copy_directory(Application ${CMAKE_SOURCE_DIR}/gamedata ${PROJECT_BINARY_DIR}/gamedata)