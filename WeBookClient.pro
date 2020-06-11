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
INCLUDEPATH *= src/QtAES

DEPENDSPATH *= .
DEPENDSPATH *= src/
DEPENDSPATH *= src/QtAES

# Headers files
HEADERS     *= src/aboutdialog.h
HEADERS     *= src/webookcommon.h
HEADERS     *= src/mainwindow.h
HEADERS     *= src/webookman.h
HEADERS     *= src/treeitem.h
HEADERS     *= src/treemodel.h
HEADERS     *= src/treeviewdragdropmodel.h
# Source files
SOURCES     *= src/aboutdialog.cpp
SOURCES     *= src/webookcommon.cpp
SOURCES     *= src/mainwindow.cpp
SOURCES     *= src/webookman.cpp
SOURCES     *= src/treeitem.cpp
SOURCES     *= src/treemodel.cpp
SOURCES     *= src/treeviewdragdropmodel.cpp
SOURCES     *= src/main.cpp
# Ui Form(s)
FORMS       += src/mainwindow.ui
FORMS       += src/aboutdialog.ui
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
###############################################################################
HEADERS     *= src/qlogger.h
SOURCES     *= src/qlogger.cpp
###############################################################################
# https://github.com/bricke/Qt-AES                                            #
###############################################################################
#QT          *= testlib
#
SOURCES     *= src/QtAES/qaesencryption.cpp
#SOURCES     *= src/QtAES/maintest.cpp
#SOURCES     *= src/QtAES/unit_test/aestest.cpp
#
HEADERS     *= src/QtAES/qaesencryption.h
#HEADERS     *= src/QtAES/unit_test/aestest.h
#
#DISTFILES   *= src/QtAES/unit_test/longText.txt
#RESOURCES   *= src/QtAES/res.qrc
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


