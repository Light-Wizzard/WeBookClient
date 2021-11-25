TEMPLATE = app
TARGET   = WeBookClient
QT      += core gui xml webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires(qtConfig(filedialog))

CONFIG += c++17


HEADERS += \
    src/BookmarkMenu.h \
    src/BookmarkView.h \
    src/HelpTab.h \
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
    src/HelpTab.cpp \
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
    scripts/testPS.ps1 \
    scripts/upload.sh

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/webenginewidgets/simplebrowser
#INSTALLS += target
