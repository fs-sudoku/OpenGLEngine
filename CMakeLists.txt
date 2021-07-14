cmake_minimum_required (VERSION 3.8)

project(Application)

set(IS_DEBUG 1)
set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

set(SOURCE_FILES
"src/main.cpp"
"src/core/core.cpp"
"src/engine/camera.cpp"
"src/engine/manager.cpp"
"src/engine/updatable_object.cpp"
"src/memory/memory.cpp"
"src/render/render.cpp"
"src/render/shader.cpp"
"src/scripting/lua_manager.cpp"
"src/scripting/scriptable_object.cpp"
"src/utils/file_io.cpp"
"src/utils/utils.cpp"
"src/render/shader_processor.h" 
"src/render/shader_processor.cpp")

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