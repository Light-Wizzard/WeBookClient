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

#include "browser.h"
#include "browserwindow.h"

/*****************************************************************************/
/**
 * @brief Browser::Browser
 */
Browser::Browser(QWidget *parent) : QWidget(parent)
{
    // Quit application if the download manager window is the only remaining window
    myDownloadManagerWidget.setAttribute(Qt::WA_QuitOnClose, false);
    //
    QObject::connect(QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested, &myDownloadManagerWidget, &DownloadManagerWidget::downloadRequested);
}
/*****************************************************************************/
/**
 * @brief Browser::createWindow
 * @param offTheRecord
 * @return
 */
BrowserWindow *Browser::createWindow(bool offTheRecord)
{
    if (offTheRecord && !myOtrProfile)
    {
        myOtrProfile.reset(new QWebEngineProfile);
        QObject::connect(myOtrProfile.get(), &QWebEngineProfile::downloadRequested, &myDownloadManagerWidget, &DownloadManagerWidget::downloadRequested);
    }
    auto profile = offTheRecord ? myOtrProfile.get() : QWebEngineProfile::defaultProfile();
    auto mainWindow = new BrowserWindow(createBookmarkMenu(), this, profile, false);
    myBrowserWindows.append(mainWindow);
    QObject::connect(mainWindow, &QObject::destroyed, this, [this, mainWindow]() { myBrowserWindows.removeOne(mainWindow); });
    mainWindow->show();
    return mainWindow;
}
/*****************************************************************************/
/**
 * @brief Browser::createDevToolsWindow
 * @return
 */
BrowserWindow *Browser::createDevToolsWindow()
{
    auto profile = QWebEngineProfile::defaultProfile();
    auto mainWindow = new BrowserWindow(createBookmarkMenu(), this, profile, true);
    myBrowserWindows.append(mainWindow);
    QObject::connect(mainWindow, &QObject::destroyed, this, [this, mainWindow]() { myBrowserWindows.removeOne(mainWindow); });
    mainWindow->show();
    return mainWindow;
}
/*****************************************************************************/
/**
 * @brief BrowserWindow::createBookmarkMenu
 * @return
 */
QMenu *Browser::createBookmarkMenu()
{
    auto *myMenuWidget = new QMenu(tr("&Bookmarks"));
    //QAction *addAction = myMenuWidget->addAction(tr("&Add"));
    //connect(addAction, &QAction::triggered, myTabWidget, &TabWidget::createBookmarkTab);
    //myMenuWidget->addAction(tr("Add"), this, &TabWidget::createBookmarkTab);
    return myMenuWidget;
}
/******************************* End of File *********************************/
