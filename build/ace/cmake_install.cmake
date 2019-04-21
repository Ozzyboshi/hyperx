# Install script for directory: /root/ACE

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/root/ACE/game/build/ace/libace.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace" TYPE FILE FILES
    "/root/ACE/include/ace/macros.h"
    "/root/ACE/include/ace/types.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/generic" TYPE FILE FILES
    "/root/ACE/include/ace/generic/main.h"
    "/root/ACE/include/ace/generic/screen.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/utils" TYPE FILE FILES
    "/root/ACE/include/ace/utils/bitmap.h"
    "/root/ACE/include/ace/utils/bmframe.h"
    "/root/ACE/include/ace/utils/chunky.h"
    "/root/ACE/include/ace/utils/custom.h"
    "/root/ACE/include/ace/utils/dir.h"
    "/root/ACE/include/ace/utils/endian.h"
    "/root/ACE/include/ace/utils/extview.h"
    "/root/ACE/include/ace/utils/file.h"
    "/root/ACE/include/ace/utils/font.h"
    "/root/ACE/include/ace/utils/palette.h"
    "/root/ACE/include/ace/utils/tag.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/managers" TYPE FILE FILES
    "/root/ACE/include/ace/managers/audio.h"
    "/root/ACE/include/ace/managers/blit.h"
    "/root/ACE/include/ace/managers/copper.h"
    "/root/ACE/include/ace/managers/game.h"
    "/root/ACE/include/ace/managers/joy.h"
    "/root/ACE/include/ace/managers/key.h"
    "/root/ACE/include/ace/managers/log.h"
    "/root/ACE/include/ace/managers/memory.h"
    "/root/ACE/include/ace/managers/mouse.h"
    "/root/ACE/include/ace/managers/rand.h"
    "/root/ACE/include/ace/managers/system.h"
    "/root/ACE/include/ace/managers/timer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/ace/managers/viewport" TYPE FILE FILES
    "/root/ACE/include/ace/managers/viewport/camera.h"
    "/root/ACE/include/ace/managers/viewport/scrollbuffer.h"
    "/root/ACE/include/ace/managers/viewport/simplebuffer.h"
    "/root/ACE/include/ace/managers/viewport/tilebuffer.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/fixmath" TYPE FILE FILES
    "/root/ACE/include/fixmath/fix16.h"
    "/root/ACE/include/fixmath/fix16_trig_sin_lut.h"
    "/root/ACE/include/fixmath/fixmath.h"
    "/root/ACE/include/fixmath/fract32.h"
    "/root/ACE/include/fixmath/int64.h"
    "/root/ACE/include/fixmath/uint32.h"
    )
endif()

