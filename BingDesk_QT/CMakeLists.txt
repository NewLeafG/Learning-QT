cmake_minimum_required(VERSION 3.16)

project(BingDesk_QT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Network Qml Quick Concurrent)

qt_standard_project_setup()

qt_add_executable(appBingDesk_QT
    main.cpp
)

qt_add_qml_module(appBingDesk_QT
    URI BingDesk_QT
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES wallpapermanager.h wallpapermanager.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBingDesk_QT PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBingDesk_QT
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appBingDesk_QT PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Qml
    Qt::Quick
    Qt::Concurrent
)

include(GNUInstallDirs)
install(TARGETS appBingDesk_QT
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
