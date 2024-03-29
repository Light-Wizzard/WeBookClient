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

#include "DownloadManagerWidget.h"
#include "Browser.h"
#include "BrowserWindow.h"
#include "DownloadWidget.h"

/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::DownloadManagerWidget
 * @param parent
 */
DownloadManagerWidget::DownloadManagerWidget(QWidget *parent) : QWidget(parent), ui(new Ui::DownloadManagerWidget), myNumDownloads(0)
{
    ui->setupUi(this);
}
/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::~DownloadManagerWidget
 */
DownloadManagerWidget::~DownloadManagerWidget()
{
    delete ui;
}
/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::downloadRequested
 * @param download
 */
void DownloadManagerWidget::downloadRequested(QWebEngineDownloadItem *download)
{
    Q_ASSERT(download && download->state() == QWebEngineDownloadItem::DownloadRequested);

    #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QString path = QFileDialog::getSaveFileName(this, tr("Save as"), QDir(download->downloadDirectory()).filePath(download->downloadFileName()));
    #else
    QString path = QFileDialog::getSaveFileName(this, tr("Save as"), download->path());
    #endif
    if (path.isEmpty()) { return; }

    #if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    download->setDownloadDirectory(QFileInfo(path).path());
    download->setDownloadFileName(QFileInfo(path).fileName());
    #else
    download->setPath(path);
    #endif
    download->accept();
    add(new DownloadWidget(download));

    show();
}
/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::add
 * @param downloadWidget
 */
void DownloadManagerWidget::add(DownloadWidget *downloadWidget)
{
    connect(downloadWidget, &DownloadWidget::removeClicked, this, &DownloadManagerWidget::remove);
    ui->layoutItems->insertWidget(0, downloadWidget, 0, Qt::AlignTop);
    if (myNumDownloads++ == 0) { ui->labelZeroItems->hide(); }
}
/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::remove
 * @param downloadWidget
 */
void DownloadManagerWidget::remove(DownloadWidget *downloadWidget)
{
    ui->layoutItems->removeWidget(downloadWidget);
    downloadWidget->deleteLater();
    if (--myNumDownloads == 0) { ui->labelZeroItems->show(); }
}
/*****************************************************************************/
/**
 * @brief DownloadManagerWidget::favIcon
 * @return
 */
QIcon DownloadManagerWidget::favIcon() const
{
    // FIXME icon
    static QIcon theFavIcon(QStringLiteral(":go-bottom.png"));
    return theFavIcon;
}
/******************************* End of File *********************************/
