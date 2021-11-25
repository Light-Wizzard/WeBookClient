TEMPLATE = app
TARGET   = WeBookClient
QT      += core gui xml webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(filedialog))

CONFIG += c++17


HEADERS += \
    src/BookmarkMenu.h \
    src/BookmarkView.h \
    src/TreeWidgetView.h \
    src/XbelMenuReader.h \
    src/XbelTreeReader.h \
    src/browser.h \
    src/browserwindow.h \
    src/downloadmanagerwidget.h \
    src/downloadwidget.h \
    src/tabwidget.h \
    src/webpage.h \
    src/webpopupwindow.h \
    src/webview.h \
    src/xbelwriter.h

SOURCES += \
    src/BookmarkMenu.cpp \
    src/BookmarkView.cpp \
    src/TreeWidgetView.cpp \
    src/XbelMenuReader.cpp \
    src/XbelTreeReader.cpp \
    src/browser.cpp \
    src/browserwindow.cpp \
    src/downloadmanagerwidget.cpp \
    src/downloadwidget.cpp \
    src/main.cpp \
    src/tabwidget.cpp \
    src/webpage.cpp \
    src/webpopupwindow.cpp \
    src/webview.cpp \
    src/xbelwriter.cpp

FORMS += \
    src/certificateerrordialog.ui \
    src/passworddialog.ui \
    src/downloadmanagerwidget.ui \
    src/downloadwidget.ui

RESOURCES += WeBookClient.qrc

DISTFILES += bookmarks.xbel \
    README.md

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/webenginewidgets/simplebrowser
#INSTALLS += target
