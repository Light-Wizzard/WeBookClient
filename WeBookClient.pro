TEMPLATE = app
TARGET   = WeBookClient
QT      += core gui xml webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(filedialog))

CONFIG += c++17


HEADERS += \
    src/BookmarkMenu.h \
    src/BookmarkView.h \
    src/Browser.h \
    src/BrowserWindow.h \
    src/DownloadManagerWidget.h \
    src/DownloadWidget.h \
    src/HelpView.h \
    src/TabWidget.h \
    src/TreeWidgetView.h \
    src/WebPage.h \
    src/WebPopupWindow.h \
    src/WebView.h \
    src/XbelMenuReader.h \
    src/XbelTreeReader.h \
    src/XbelTreeWriter.h

SOURCES += \
    src/BookmarkMenu.cpp \
    src/BookmarkView.cpp \
    src/Browser.cpp \
    src/BrowserWindow.cpp \
    src/DownloadManagerWidget.cpp \
    src/DownloadWidget.cpp \
    src/HelpView.cpp \
    src/TabWidget.cpp \
    src/TreeWidgetView.cpp \
    src/WebPage.cpp \
    src/WebPopupWindow.cpp \
    src/WebView.cpp \
    src/XbelMenuReader.cpp \
    src/XbelTreeReader.cpp \
    src/XbelTreeWriter.cpp \
    src/main.cpp

FORMS += \
    src/DownloadManagerWidget.ui \
    src/DownloadWidget.ui \
    src/certificateerrordialog.ui \
    src/passworddialog.ui

RESOURCES += WeBookClient.qrc
CONFIG += localize_deployment
SYMBIAN_SUPPORTED_LANGUAGES += zh_CN
SYMBIAN_LANG.zh_CN = 31
CONFIG += lrelease
CONFIG += embed_translations
LRELEASE_DIR=./translations
QM_FILES_RESOURCE_PREFIX=./translations
# ar,de,en,es,fr,it,ja,no,ru,sv,zh_CN
TRANSLATIONS += translations/WeBookClient_ar.ts \
                translations/WeBookClient_de.ts \
                translations/WeBookClient_en.ts \
                translations/WeBookClient_es.ts \
                translations/WeBookClient_fr.ts \
                translations/WeBookClient_it.ts \
                translations/WeBookClient_ja.ts \
                translations/WeBookClient_no.ts \
                translations/WeBookClient_ru.ts \
                translations/WeBookClient_sv.ts \
                translations/WeBookClient_zh_CN.ts

DISTFILES += bookmarks.xbel README.md \
    .appveyor.yml \
    CMakeLists.txt \
    scripts/build_script.ps1 \
    scripts/build_script.sh \
    scripts/build_script_mac.sh \
    scripts/install.ps1 \
    scripts/install.sh \
    scripts/install_mac.sh \
    scripts/test.sh \
    scripts/testPS.ps1 \
    scripts/upload.sh

# install
#target.path = /usr/bin
target.path = /usr
INSTALLS += target
