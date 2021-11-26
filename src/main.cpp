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

#include "Browser.h"
#include "BrowserWindow.h"
#include "TabWidget.h"
#include <QApplication>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QtGlobal>

#if Q_OS_MSDOS || defined(Q_OS_WIN32) || defined(Q_OS_WINCE)
    #define VERSION "1.0.0"
#else
    #define VERSION "1.0"
#endif
/*****************************************************************************/
/**
 * @brief commandLineUrlArgument
 * @return
 */
QUrl commandLineUrlArgument()
{
    const QStringList args = QCoreApplication::arguments();
    for (int i = 1; i < args.size(); i++)
    {
        if (!args.at(i).startsWith(QLatin1Char('-'))) { return QUrl::fromUserInput(args.at(i)); }
    }
    return QUrl(QStringLiteral("https://www.qt.io"));
}
/*****************************************************************************/
/**
 * @brief main
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
    QString theAppName = "WeBookClient";
    QString theAppDisplayName = "WeBookClient";
    //
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    //
    // Load Resource File WeBookClient.qrc before creating Application
    Q_INIT_RESOURCE(WeBookClient);
    //
    QApplication theApplication(argc, argv);
    theApplication.setWindowIcon(QIcon(QStringLiteral(":AppLogoColor.png")));
    // Setup the Application for MyOrgSettings
    theApplication.setOrganizationName(theAppName);
    theApplication.setApplicationName(theAppName);
    theApplication.setApplicationDisplayName(theAppDisplayName);
    theApplication.setApplicationVersion(VERSION);
    //
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::DnsPrefetchEnabled, true);
    QWebEngineProfile::defaultProfile()->setUseForGlobalCertificateVerification();
    #endif
    //
    QUrl url = commandLineUrlArgument();
    //
    Browser browser;
    BrowserWindow *window = browser.createWindow();
    window->tabWidget()->setUrl(url);

    return theApplication.exec();
}
/******************************* End of File *********************************/
