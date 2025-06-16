cmake_minimum_required(VERSION 3.5)

project(App VERSION 0.1 LANGUAGES CXX)
add_subdirectory(qtkeychain)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

# Set the output directory for generated UI files to the same folder as source files
set(CMAKE_AUTOUIC_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/ui)

set(CMAKE_PREFIX_PATH "C:/QT/6.6.2/mingw_64")

set(Qt6_DIR "C:/QT/6.6.2/mingw_64/lib/cmake/Qt6")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS Core Gui Widgets Network Test REQUIRED)

set(TS_FILES App_ro_RO.ts)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_SOURCE_DIR}/qtkeychain/qtkeychain
    ${CMAKE_SOURCE_DIR}/qtkeychain/build/qtkeychain
)

set(PROJECT_SOURCES
    src/mainwindow.cpp
    src/strategy.cpp
    src/strategydialog.cpp
    src/initiatedstrategy.cpp
    src/EncryptionHelper.cpp
    src/SettingsManager.cpp
    src/QtKeychainWrapper.cpp
    src/ScriptManager.cpp
    include/mainwindow.hpp
    include/strategy.hpp
    include/strategydialog.hpp
    include/initiatedstrategy.hpp
    include/EncryptionHelper.hpp
    include/SettingsManager.hpp
    include/QtKeychainWrapper.hpp
    include/ScriptManager.hpp
    include/TechnicalIndicatorUtils.hpp
    src/ui/mainwindow.ui
    src/ui/strategydialog.ui
    src/ui/initiatedstrategy.ui
    main.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(App
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(App SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(App
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

link_directories(${CMAKE_SOURCE_DIR}/qtkeychain/build/lib)

# Add Qt5::Network module to your target_link_libraries
target_link_libraries(App PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network qt6keychain)

# Link Boost libraries to your target
target_link_libraries(App PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${BOOST_LIBRARY_DIR})

# Link with the Winsock library
target_link_libraries(App PRIVATE ws2_32)

file(GLOB SCRIPTS "${CMAKE_CURRENT_SOURCE_DIR}/scripts/*")

# Copy scripts after build
add_custom_command(TARGET App POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/scripts"
    "$<TARGET_FILE_DIR:App>"
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.App)
endif()
set_target_properties(App PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS App
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(App)
endif()

# enable_testing()

# add_executable(EncryptionHelperTests
#     tests/EncryptionHelperTests.cpp
#     src/EncryptionHelper.cpp
#     src/QtKeychainWrapper.cpp
# )
# target_link_libraries(EncryptionHelperTests PRIVATE Qt6::Core Qt6::Test qt6keychain)

# add_test(NAME EncryptionHelperTests COMMAND EncryptionHelperTests)

# add_executable(SettingsManagerTests
#     tests/SettingsManagerTests.cpp
#     src/SettingsManager.cpp
# )
# target_link_libraries(SettingsManagerTests PRIVATE Qt6::Core Qt6::Test)
# add_test(NAME SettingsManagerTests COMMAND SettingsManagerTests)

# add_executable(ScriptManagerTests
#     tests/ScriptManagerTests.cpp
#     src/ScriptManager.cpp
# )
# target_link_libraries(ScriptManagerTests PRIVATE Qt6::Core Qt6::Test)
# add_test(NAME ScriptManagerTests COMMAND ScriptManagerTests)