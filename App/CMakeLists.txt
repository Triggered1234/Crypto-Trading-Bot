cmake_minimum_required(VERSION 3.5)

project(App VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the output directory for generated UI files to the same folder as source files
set(CMAKE_AUTOUIC_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_PREFIX_PATH "C:/QT/6.6.2/mingw_64")

set(Qt6_DIR "C:/QT/6.6.2/mingw_64/lib/cmake/Qt6")


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt6 COMPONENTS Core Gui Widgets Network REQUIRED)

set(TS_FILES App_ro_RO.ts)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(App
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        strategy.h strategy.cpp
        strategydialog.h strategydialog.cpp strategydialog.ui
        initiatedstrategy.h initiatedstrategy.cpp initiatedstrategy.ui

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

# Add Qt5::Network module to your target_link_libraries
target_link_libraries(App PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network)

# Link Boost libraries to your target
target_link_libraries(App PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${BOOST_LIBRARY_DIR})

# Link with the Winsock library
target_link_libraries(App PRIVATE ws2_32)

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
