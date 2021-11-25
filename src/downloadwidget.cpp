/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
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

#include "downloadwidget.h"

#include <QFileInfo>
#include <QUrl>
#include <QWebEngineDownloadItem>

/*****************************************************************************/
/**
 * @brief DownloadWidget::DownloadWidget
 * @param download
 * @param parent
 */
DownloadWidget::DownloadWidget(QWebEngineDownloadItem *download, QWidget *parent) : QFrame(parent), myDownload(download), myTimeAdded()
{
    myTimeAdded.start();
    setupUi(this);
    #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    lableDstName->setText(myDownload->downloadFileName());
    #else
    lableDstName->setText(QFileInfo(myDownload->path()).fileName());
    #endif
    lableSrcUrl->setText(myDownload->url().toDisplayString());

    connect(buttonCancel, &QPushButton::clicked, [this](bool)
    {
        if (myDownload->state() == QWebEngineDownloadItem::DownloadInProgress)  { myDownload->cancel(); }
        else { emit removeClicked(this); }
    });
    connect(myDownload, &QWebEngineDownloadItem::downloadProgress, this, &DownloadWidget::updateWidget);
    connect(myDownload, &QWebEngineDownloadItem::stateChanged, this, &DownloadWidget::updateWidget);
    updateWidget();
}
/*****************************************************************************/
/**
 * @brief DownloadWidget::withUnit
 * @param bytes
 * @return
 */
inline QString DownloadWidget::withUnit(qreal bytes)
{
    if (bytes < (1 << 10))      { return tr("%L1 B").arg(bytes); }
    else if (bytes < (1 << 20)) { return tr("%L1 KiB").arg(bytes / (1 << 10), 0, 'f', 2); }
    else if (bytes < (1 << 30)) { return tr("%L1 MiB").arg(bytes / (1 << 20), 0, 'f', 2); }
    else                        { return tr("%L1 GiB").arg(bytes / (1 << 30), 0, 'f', 2); }
}
/*****************************************************************************/
/**
 * @brief DownloadWidget::updateWidget
 */
void DownloadWidget::updateWidget()
{
    qreal totalBytes = myDownload->totalBytes();
    qreal receivedBytes = myDownload->receivedBytes();
    qreal bytesPerSecond = receivedBytes / myTimeAdded.elapsed() * 1000;

    auto state = myDownload->state();
    switch (state)
    {
        case QWebEngineDownloadItem::DownloadRequested:
            Q_UNREACHABLE();
            break;
        case QWebEngineDownloadItem::DownloadInProgress:
            if (totalBytes >= 0)
            {
                progressBar->setValue(qRound(100 * receivedBytes / totalBytes));
                progressBar->setDisabled(false);
                progressBar->setFormat(tr("%p% - %1 of %2 downloaded - %3/s").arg(withUnit(receivedBytes), withUnit(totalBytes), withUnit(bytesPerSecond)));
            }
            else
            {
                progressBar->setValue(0);
                progressBar->setDisabled(false);
                progressBar->setFormat(tr("unknown size - %1 downloaded - %2/s").arg(withUnit(receivedBytes), withUnit(bytesPerSecond)));
            }
            break;
        case QWebEngineDownloadItem::DownloadCompleted:
            progressBar->setValue(100);
            progressBar->setDisabled(true);
            progressBar->setFormat(tr("completed - %1 downloaded - %2/s").arg(withUnit(receivedBytes), withUnit(bytesPerSecond)));
            break;
        case QWebEngineDownloadItem::DownloadCancelled:
            progressBar->setValue(0);
            progressBar->setDisabled(true);
            progressBar->setFormat(tr("cancelled - %1 downloaded - %2/s").arg(withUnit(receivedBytes), withUnit(bytesPerSecond)));
            break;
        case QWebEngineDownloadItem::DownloadInterrupted:
            progressBar->setValue(0);
            progressBar->setDisabled(true);
            progressBar->setFormat(tr("interrupted: %1").arg(myDownload->interruptReasonString()));
            break;
    }

    if (state == QWebEngineDownloadItem::DownloadInProgress)
    {
        static QIcon cancelIcon(QStringLiteral(":process-stop.png"));
        buttonCancel->setIcon(cancelIcon);
        buttonCancel->setToolTip(tr("Stop downloading"));
    }
    else
    {
        static QIcon removeIcon(QStringLiteral(":edit-clear.png"));
        buttonCancel->setIcon(removeIcon);
        buttonCancel->setToolTip(tr("Remove from list"));
    }
}
/******************************* End of File *********************************/
