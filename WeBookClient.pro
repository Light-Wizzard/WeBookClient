# WeBookServerClient.pro
#DEFINES         *= QT_PRINTSUPPORT_LIB
#qtHaveModule(printsupport): QT *= printsupport
QT *= printsupport
# Specifies the name of the template to use when generating the project.
# The allowed values are: app, lib, subdirs, aux, vcapp or vclib
TEMPLATE     = "app"
# Specifies the name of the target file. Contains the base name of the project file by default.
# Do not use Spaces in Target Name
# This pro(ject) file is based on a pattern
TARGET       = "WeBookClient"
#
INCLUDEPATH     += .
INCLUDEPATH     += src/
INCLUDEPATH     += "${QT_INSTALL_LIBS}/qt"
#
DEPENDPATH      += src/
#
QT              += gui
QT              += core
QT              += widgets
#QT              *= core-private
!win32:QT       *= network

CONFIG          *= qt
#CONFIG          *= "c++11"
CONFIG          *= "c++14"
#CONFIG         *= "c++1z"
#CONFIG         *= "c++17"
#CONFIG         *= "c++2a"
#CONFIG         *= "c++latest"
#TRANSLATIONS    += src/WeBookServer_en_US.ts
CONFIG          *= warn_on utf8_source executable
# Version Numver Controls
win32:VERSION   = 0.1.0.0 # major.minor.patch.build
else:VERSION    = 0.1.0   # major.minor.patch
DEFINES         = APP_VERSION=\\\"$${VERSION}\\\"
#
#include(src/WeBookClient.pri)
#include(WeBookClient.pri)
# Include Path Current path, defined in MY_CUSTOM_SOURCE_HEADER_UI_FOLDER_NAME i.e. src
INCLUDEPATH *= .
INCLUDEPATH *= src/

DEPENDSPATH *= .
DEPENDSPATH *= src/

# Headers files
HEADERS     *= src/AboutDialog.h \
    src/QLogger/QLoggerConstants.h
HEADERS     *= src/WeBookCrypto.h
HEADERS     *= src/MainWindow.h
HEADERS     *= src/WeBookMan.h
HEADERS     *= src/TreeItem.h
HEADERS     *= src/TreeModel.h
HEADERS     *= src/TreeViewDragDropModel.h
# Source files
SOURCES     *= src/AboutDialog.cpp
SOURCES     *= src/WeBookCrypto.cpp
SOURCES     *= src/MainWindow.cpp
SOURCES     *= src/WeBookMan.cpp
SOURCES     *= src/TreeItem.cpp
SOURCES     *= src/TreeModel.cpp
SOURCES     *= src/TreeViewDragDropModel.cpp
SOURCES     *= src/main.cpp
# Ui Form(s)
FORMS       += src/MainWindow.ui
FORMS       += src/AboutDialog.ui
#
DISTFILES   += data/WeBookClient.ini
DISTFILES   += data/WeBook.toc
DISTFILES   += data/WeBooks.cat
DISTFILES   += data/urllist.txt
DISTFILES   += README.md
#
RESOURCES   += WeBookClient.qrc

###############################################################################
# https://github.com/Light-Wizzard/QLogger                                    #
# Fork: https://github.com/francescmm/QLogger                                 #
###############################################################################
HEADERS     *= src/QLogger/QLogger.h
HEADERS     *= src/QLogger/QLoggerLevel.h
HEADERS     *= src/QLogger/QLoggerWriter.h
SOURCES     *= src/QLogger/QLogger.cpp
SOURCES     *= src/QLogger/QLoggerWriter.cpp
#
HEADERS     *= src/QLogger/QLoggerCommon.h
HEADERS     *= src/QLogger/QLoggerWrapper.h
SOURCES     *= src/QLogger/QLoggerCommon.cpp
SOURCES     *= src/QLogger/QLoggerWrapper.cpp
###############################################################################
# https://github.com/bricke/Qt-AES                                            #
###############################################################################
INCLUDEPATH *= src/QtAES
DEPENDSPATH *= src/QtAES
#
SOURCES     *= src/QtAES/QAESEncryption.cpp
HEADERS     *= src/QtAES/QAESEncryption.h
# Test
#QT          += testlib
#HEADERS     *= src/QtAES/unit_test/aestest.h
#SOURCES     *= src/QtAES/maintest.cpp
#SOURCES     *= src/QtAES/unit_test/aestest.cpp
##
#DISTFILES   *= src/QtAES/unit_test/longText.txt
#RESOURCES   *= src/QtAES/res.qrc
###############################################################################
#
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
#
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#
macos:QMAKE_INFO_PLIST = macos/Info.plist
ios:QMAKE_INFO_PLIST = ios/Info.plist
#
DESTDIR = "$${OUT_PWD}"
release: DESTDIR = "$${OUT_PWD}/build/release"
debug:   DESTDIR = "$${OUT_PWD}/build/debug"

OBJECTS_DIR = "$${DESTDIR}/obj"
MOC_DIR     = "$${DESTDIR}/moc"
RCC_DIR     = "$${DESTDIR}/qrc"
UI_DIR      = "$${DESTDIR}/ui"
#
unix {
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    target.path         = "$${PREFIX}/bin"
    shortcutfiles.files = "usr/share/applications/$${TARGET}.desktop"
    shortcutfiles.path  = usr/share/applications
    data.files         += "usr/share/icons/hicolor/48x48/apps/$${TARGET}.png"
    data.path           = usr/share/pixmaps
    INSTALLS           += shortcutfiles
    INSTALLS           += data
    INSTALLS           += target
    macx {
        RC_FILE = macos/Icon.icns
    }
}
################################ End of File ##################################


