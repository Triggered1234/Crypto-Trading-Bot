#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "qt6keychain" for configuration "Debug"
set_property(TARGET qt6keychain APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(qt6keychain PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/libqt6keychaind.dll.a"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libqt6keychaind.dll"
  )

list(APPEND _cmake_import_check_targets qt6keychain )
list(APPEND _cmake_import_check_files_for_qt6keychain "${_IMPORT_PREFIX}/lib/libqt6keychaind.dll.a" "${_IMPORT_PREFIX}/bin/libqt6keychaind.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
