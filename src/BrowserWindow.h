/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QTime>
#include <QWebEnginePage>
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QScreen>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    #include <QWebEngineFindTextResult>
#endif
#include <QWebEngineProfile>
//
#include "DownloadManagerWidget.h"
#include "TabWidget.h"
#include "WebView.h"
#include "TreeWidgetView.h"
#include "BookmarkMenu.h"
#include "Browser.h"


QT_BEGIN_NAMESPACE
class QLineEdit;
class QProgressBar;
class QTreeWidget;
QT_END_NAMESPACE

class Browser;
class TabWidget;
class WebView;

/*****************************************************************************/
/**
 * @brief The BrowserWindow class
 */
class BrowserWindow : public QMainWindow
{
        Q_OBJECT

    public:
        BrowserWindow(QMenu *thisMenuWidget, Browser *browser, QWebEngineProfile *profile, bool forDevTools = false);
        ~BrowserWindow();
        //
        QSize sizeHint() const override;
        TabWidget *tabWidget() const;
        WebView *currentTab() const;
        Browser *browser() { return myBrowser; }

    protected:
        void closeEvent(QCloseEvent *event) override;

    public slots:
        #if !defined(QT_NO_CONTEXTMENU) && !defined(QT_NO_CLIPBOARD)
        void onCustomContextMenuRequested(const QPoint &pos);
        #endif
        //
        void onBookmarkUrl();
        void onSetHelpTab();
        void onDownloadTab();

    private slots:
        void handleNewWindowTriggered();
        void handleNewIncognitoWindowTriggered();
        void handleFileOpenTriggered();
        void handleFindActionTriggered();
        void handleShowWindowTriggered();
        void handleWebViewLoadProgress(int);
        void handleWebViewTitleChanged(const QString &title);
        void handleWebActionEnabledChanged(QWebEnginePage::WebAction action, bool enabled);
        void handleDevToolsRequested(QWebEnginePage *source);
        #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
        void handleFindTextFinished(const QWebEngineFindTextResult &result);
        #endif

    private:
        QMenu    *createFileMenu(TabWidget *tabWidget);
        QMenu    *createEditMenu();
        QMenu    *createViewMenu(QToolBar *toolBar);
        QMenu    *createWindowMenu(TabWidget *tabWidget);
        QMenu    *createHelpMenu();
        QToolBar *createToolBar();

        QMenu                   *myMenuWidget = nullptr;
        Browser                 *myBrowser = nullptr;
        QWebEngineProfile       *myProfile = nullptr;
        TabWidget               *myTabWidget = nullptr;
        QProgressBar            *myProgressBar = nullptr;
        TreeWidgetView          *myTreeWidget = nullptr;
        QAction                 *myHistoryBackAction = nullptr;
        QAction                 *myHistoryForwardAction = nullptr;
        QAction                 *myStopAction = nullptr;
        QAction                 *myReloadAction = nullptr;
        QAction                 *myStopReloadAction = nullptr;
        QAction                 *myFavAction = nullptr;
        QLineEdit               *myUrlLineEdit = nullptr;
        QString                  myLastSearch;
        BookmarkMenu            *myBookmarkMenuWidgetView = nullptr;
        DownloadManagerWidget   *myDownloadManagerWidget = nullptr;

}; // end class BrowserWindow
#endif // BROWSERWINDOW_H
/******************************* End of File *********************************/
