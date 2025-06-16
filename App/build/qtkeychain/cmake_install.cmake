# Install script for directory: C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/qtkeychain

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/App")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "C:/QT/Tools/mingw1120_64/bin/objdump.exe")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/qtkeychain/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/mkspecs/modules" TYPE FILE FILES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/qt_Qt6Keychain.pri")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain/Qt6KeychainLibraryDepends.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain/Qt6KeychainLibraryDepends.cmake"
         "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/CMakeFiles/Export/604b9d87ca9ebe99146ebf18c5f375e6/Qt6KeychainLibraryDepends.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain/Qt6KeychainLibraryDepends-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain/Qt6KeychainLibraryDepends.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain" TYPE FILE FILES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/CMakeFiles/Export/604b9d87ca9ebe99146ebf18c5f375e6/Qt6KeychainLibraryDepends.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain" TYPE FILE FILES "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/CMakeFiles/Export/604b9d87ca9ebe99146ebf18c5f375e6/Qt6KeychainLibraryDepends-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Qt6Keychain" TYPE FILE FILES
    "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/Qt6KeychainConfig.cmake"
    "C:/Users/adria/Documents/Crypto/Crypto-Trading-Bot/Crypto-Trading-Bot/App/build/qtkeychain/Qt6KeychainConfigVersion.cmake"
    )
endif()

