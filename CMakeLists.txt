cmake_minimum_required(VERSION 3.16.2)
# I tried to put stuff you need to exit at the top
project(WeBookClient VERSION 0.1.0.0 DESCRIPTION "WeBookClient" LANGUAGES C CXX)
# Set this to your URL
set(MY_URL "light-wizzard.github.io")
# ON OFF
set(MY_QML OFF)
# Set Target Name
set(MY_TARGET ${CMAKE_PROJECT_NAME})
# If you have a project that has an SQL verion for Desktops, and No SQL for WebAssempy set both below comments
set(USE_SQL_FLAG OFF)
#
if(${CMAKE_VERSION} VERSION_GREATER "3.12.0") 
    add_compile_definitions(USE_SQL_FLAG)
else()
    add_compile_options(-D USE_SQL_FLAG)
endif()
# UI Files
set(MY_UI_FILES
    src/DownloadManagerWidget.ui
    src/DownloadWidget.ui
    src/certificateerrordialog.ui
    src/passworddialog.ui
)
# TS Files
set(MY_TS_FILES
    translations/${MY_TARGET}_ar.ts
    translations/${MY_TARGET}_de.ts
    translations/${MY_TARGET}_en.ts
    translations/${MY_TARGET}_es.ts
    translations/${MY_TARGET}_fr.ts
    translations/${MY_TARGET}_it.ts
    translations/${MY_TARGET}_ja.ts
    translations/${MY_TARGET}_no.ts
    translations/${MY_TARGET}_ru.ts
    translations/${MY_TARGET}_sv.ts
    translations/${MY_TARGET}_zh_CN.ts
)
# QM Files
set(MY_QM_FILES
    translations/${MY_TARGET}_ar.qm
    translations/${MY_TARGET}_de.qm
    translations/${MY_TARGET}_en.qm
    translations/${MY_TARGET}_es.qm
    translations/${MY_TARGET}_fr.qm
    translations/${MY_TARGET}_it.qm
    translations/${MY_TARGET}_ja.qm
    translations/${MY_TARGET}_no.qm
    translations/${MY_TARGET}_ru.qm
    translations/${MY_TARGET}_sv.qm
    translations/${MY_TARGET}_zh_CN.qm
)
# Header Files
set(HEADERS
    src/BookmarkMenu.h
    src/BookmarkView.h
    src/Browser.h
    src/BrowserWindow.h
    src/DownloadManagerWidget.h
    src/DownloadWidget.h
    src/HelpView.h
    src/TabWidget.h
    src/TreeWidgetView.h
    src/WebPage.h
    src/WebPopupWindow.h
    src/WebView.h
    src/XbelMenuReader.h
    src/XbelTreeReader.h
    src/XbelTreeWriter.h
)
# Source Files
set(PROJECT_SOURCES
    src/BookmarkMenu.cpp
    src/BookmarkView.cpp
    src/Browser.cpp
    src/BrowserWindow.cpp
    src/DownloadManagerWidget.cpp
    src/DownloadWidget.cpp
    src/HelpView.cpp
    src/TabWidget.cpp
    src/TreeWidgetView.cpp
    src/WebPage.cpp
    src/WebPopupWindow.cpp
    src/WebView.cpp
    src/XbelMenuReader.cpp
    src/XbelTreeReader.cpp
    src/XbelTreeWriter.cpp
    src/main.cpp
    ${MY_TARGET}.qrc
    #${MY_TS_FILES}
    ${HEADERS}
)
# All Qt includes
#3DAnimation             Help                    QuickWidgets
#3DCore                  LinguistTools           RemoteObjects
#3DExtras                Location                RepParser
#3DInput                 Multimedia              Scxml
#3DLogic                 MultimediaWidgets       Sensors
#3DQuick                 Network                 SerialPort
#3DQuickAnimation        Nfc                     Sql
#3DQuickExtras           OpenGL                  Svg
#3DQuickInput            OpenGLExtensions        Test
#3DQuickRender           Positioning             TextToSpeech
#3DQuickScene2D          PositioningQuick        UiPlugin
#3DRender                PrintSupport            UiTools
#AndroidExtras           Qml                     WebChannel
#Bluetooth               Quick                   WebSockets
#Concurrent              QuickCompiler           WebView
#Core                    QuickControls2          Widgets
#Gamepad                 QuickTemplates2         Xml
#Gui                     QuickTest               XmlPatterns        WebEngineWidgets
# Find packages
if(DEFINED USE_SQL_FLAG)
    if(MY_QML)
        # QML
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Sql Qml Quick QuickControls2 PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql Qml Quick QuickControls2 PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
    else()
        # C++
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets Sql PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets Sql PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
    endif()
else()
    if(MY_QML)
        # QML
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Qml Quick QuickControls2 PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Qml Quick QuickControls2 PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
    else()
        # C++
        find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
        find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Gui Widgets PrintSupport Network Multimedia Concurrent LinguistTools Xml WebEngineWidgets REQUIRED)
    endif()
endif()
# You can turn these ON OFF individually for Translations
option(DO_LUPDATE "Create TS files lupdate, turn off after you created them" ON)
option(DO_LRELEASE "Create QM files lrelease, turn off after you created them" ON)
#
# Include GNUInstallDirs to get canonical paths
include(GNUInstallDirs)
# Set App Version
set(APP_VERSION "0.1.0")
# Set include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Auto
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# The lines below this should not need to be altered from one project to the next
# Set Properties and add executable
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${MY_TARGET} MANUAL_FINALIZATION ${PROJECT_SOURCES})
    # Define target properties for Android with Qt 6 as:
    set_property(TARGET ${MY_TARGET} APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    #qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${MY_TS_FILES})
else()
    if(ANDROID)
        add_library(${MY_TARGET} SHARED ${PROJECT_SOURCES})
        # Define properties for Android with Qt 5 after find_package() calls as:
        set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(${MY_TARGET} ${PROJECT_SOURCES})
    endif()

    #qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${MY_TS_FILES})
endif()
# Set Definitions and Library
target_compile_definitions(${MY_TARGET} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
# Libraries
if(DEFINED USE_SQL_FLAG)
    if(MY_QML)
        # QML
        target_link_libraries(${MY_TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2 Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    else()
        # C++
        target_link_libraries(${MY_TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    endif()
else()
    if(MY_QML)
        # QML
        target_link_libraries(${MY_TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::QuickControls2 Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    else()
        # C++
        target_link_libraries(${MY_TARGET} PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::PrintSupport Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::Xml Qt${QT_VERSION_MAJOR}::WebEngineWidgets)
    endif()
endif()
# Set Target Properties to include MACOS
set_target_properties(${MY_TARGET} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER ${MY_URL}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/macos/info.plist
)
# genearats ts and qm file searching recursively THIS_RC_DIR
function(generate_translations THIS_CUSTOM_TARGET THIS_TS_DIR THIS_TS_FILES THIS_RC_DIR)
    # lupdate
    if(DO_LUPDATE)
        message(STATUS "run lupdate")
        set(UPADTE_TS_TARGET_NAME ${THIS_CUSTOM_TARGET}_ts)
        add_custom_target(${UPADTE_TS_TARGET_NAME}
            COMMAND ${Qt5_LUPDATE_EXECUTABLE} -recursive ${THIS_RC_DIR} -ts ${THIS_TS_FILES}
            WORKING_DIRECTORY ${THIS_TS_DIR})
    endif()
    # lrelease
    if(DO_LRELEASE)
        message(STATUS "run lrelease")
        set(UPADTE_QM_TARGET_NAME ${THIS_CUSTOM_TARGET}_qm)
        add_custom_target(${UPADTE_QM_TARGET_NAME}
            COMMAND ${Qt5_LRELEASE_EXECUTABLE} ${THIS_TS_FILES}
            WORKING_DIRECTORY ${THIS_TS_DIR})
        add_dependencies(${UPADTE_QM_TARGET_NAME} ${UPADTE_TS_TARGET_NAME} )
        add_dependencies(${THIS_CUSTOM_TARGET} ${UPADTE_QM_TARGET_NAME})
    endif()
endfunction()
# Set variables to pass in
set(MY_TS_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(MY_SOURCE_LOOKUP_DIR ${CMAKE_CURRENT_SOURCE_DIR})
# Generate Tralations
#generate_translations(${MY_TARGET} "${MY_TS_DIR}" "${MY_TS_FILES}" "${MY_SOURCE_LOOKUP_DIR}")
# Install QM files if not APPLE
if(UNIX AND NOT APPLE)
    install(FILES ${MY_QM_FILES} DESTINATION ${CMAKE_SOURCE_DIR}/translations)
endif()
# Qt 6 stuff
if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${MY_TARGET})
    qt_finalize_executable(${MY_TARGET})
endif()
# Install Target Destinations
install(TARGETS ${MY_TARGET}
  RUNTIME DESTINATION /usr/bin
  BUNDLE DESTINATION  /usr/bin
  LIBRARY DESTINATION /usr/lib
  ARCHIVE DESTINATION /usr/lib
)
###### End of File ######
