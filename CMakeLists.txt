cmake_minimum_required(VERSION 2.8.5)
#project(hello)
project(hyperx)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

# Lowercase project name for binaries and packaging
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

if(NOT AMIGA)
	message(SEND_ERROR "This project only compiles for Amiga")
endif()

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAMIGA -Wall -Wextra -fomit-frame-pointer")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DACE_DEBUG")
file(GLOB_RECURSE SOURCES src/*.c)
file(GLOB_RECURSE HEADERS src/*.h)

include_directories(
	${PROJECT_SOURCE_DIR}/src
)

if(GAME_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DGAME_DEBUG")
endif()
if(ACE_DEBUG)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DACE_DEBUG") # For ACE headers with ifdefs
endif()

# ACE
# If you cloned ACE into subdirectory, e.g. to `deps/ace` folder, use following:
#add_subdirectory(../include/ace ace)
include_directories(/root/ACE/include)
add_subdirectory(../ ace)
# If you installed ACE, use following:
#find_package(ace REQUIRED)
include_directories(${ace_INCLUDE_DIRS})

# Linux/other UNIX get a lower-case binary name
set(TARGET_NAME ${PROJECT_NAME_LOWER})
add_executable(${TARGET_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${TARGET_NAME} ace)
target_link_libraries(
    ${TARGET_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/music_ptr_linkable.o
)