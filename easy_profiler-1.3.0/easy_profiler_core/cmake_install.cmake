# Install script for directory: /Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core

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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler" TYPE FILE FILES
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/generated/easy_profilerConfig.cmake"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/generated/easy_profilerConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/easy" TYPE FILE FILES
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/easy_net.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/easy_socket.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/easy_compiler_support.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/profiler.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/profiler_aux.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/profiler_colors.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/reader.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/serialized_block.h"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/include/easy/profiler_public_types.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/." TYPE FILE FILES
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/LICENSE.MIT"
    "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/LICENSE.APACHE"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/bin/libeasy_profiler.dylib")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libeasy_profiler.dylib" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libeasy_profiler.dylib")
    execute_process(COMMAND "/usr/bin/install_name_tool"
      -id "libeasy_profiler.dylib"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libeasy_profiler.dylib")
    execute_process(COMMAND /usr/bin/install_name_tool
      -add_rpath "$ORIGIN"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libeasy_profiler.dylib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libeasy_profiler.dylib")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler/easy_profilerTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler/easy_profilerTargets.cmake"
         "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/CMakeFiles/Export/lib/cmake/easy_profiler/easy_profilerTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler/easy_profilerTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler/easy_profilerTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler" TYPE FILE FILES "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/CMakeFiles/Export/lib/cmake/easy_profiler/easy_profilerTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/easy_profiler" TYPE FILE FILES "/Users/jason/projects/chess/git/chessai/easy_profiler-1.3.0/easy_profiler_core/CMakeFiles/Export/lib/cmake/easy_profiler/easy_profilerTargets-release.cmake")
  endif()
endif()

