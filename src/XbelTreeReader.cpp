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
#include "XbelTreeReader.h"

/*****************************************************************************/
/**
 * @brief XbelTreeReader::XbelTreeReader
 * @param treeWidget
 */
XbelTreeReader::XbelTreeReader(QTreeWidget *treeWidget) : treeWidget(treeWidget)
{
    QStyle *style = treeWidget->style();

    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirClosedIcon), QIcon::Normal, QIcon::Off);
    folderIcon.addPixmap(style->standardPixmap(QStyle::SP_DirOpenIcon),   QIcon::Normal, QIcon::On);
    bookmarkIcon.addPixmap(style->standardPixmap(QStyle::SP_FileIcon));
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::read
 * @param device
 * @return
 */
bool XbelTreeReader::read(QIODevice *device)
{
    xml.setDevice(device);

    if (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("xbel") && xml.attributes().value(versionAttribute()) == QLatin1String("1.0"))
        {
            readXBEL();
        }
        else
        {
            xml.raiseError(QObject::tr("The file is not an XBEL version 1.0 file."));
        }
    }

    return !xml.error();
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::errorString
 * @return
 */
QString XbelTreeReader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3").arg(xml.errorString()).arg(xml.lineNumber()).arg(xml.columnNumber());
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::readXBEL
 */
void XbelTreeReader::readXBEL()
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("xbel"));

    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("folder"))         { readFolder(0); }
        else if (xml.name() == QLatin1String("bookmark"))  { readBookmark(0); }
        else if (xml.name() == QLatin1String("separator")) { readSeparator(0); }
        else                                               { xml.skipCurrentElement(); }
    }
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::readTitle
 * @param item
 */
void XbelTreeReader::readTitle(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("title"));

    QString title = xml.readElementText();
    item->setText(0, title);
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::readSeparator
 * @param item
 */
void XbelTreeReader::readSeparator(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("separator"));

    QTreeWidgetItem *separator = createChildItem(item);
    separator->setFlags(item->flags() & ~Qt::ItemIsSelectable);
    separator->setText(0, QString(30, 0xB7));
    xml.skipCurrentElement();
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::readFolder
 * @param item
 */
void XbelTreeReader::readFolder(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("folder"));

    QTreeWidgetItem *folder = createChildItem(item);
    bool folded = (xml.attributes().value(foldedAttribute()) != QLatin1String("no"));
    folder->setExpanded(!folded);

    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("title"))          { readTitle(folder); }
        else if (xml.name() == QLatin1String("folder"))    { readFolder(folder); }
        else if (xml.name() == QLatin1String("bookmark"))  { readBookmark(folder); }
        else if (xml.name() == QLatin1String("separator")) { readSeparator(folder); }
        else                                               { xml.skipCurrentElement(); }
    }
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::readBookmark
 * @param item
 */
void XbelTreeReader::readBookmark(QTreeWidgetItem *item)
{
    Q_ASSERT(xml.isStartElement() && xml.name() == QLatin1String("bookmark"));

    QTreeWidgetItem *bookmark = createChildItem(item);
    bookmark->setFlags(bookmark->flags() | Qt::ItemIsEditable);
    bookmark->setIcon(0, bookmarkIcon);
    bookmark->setText(0, QObject::tr("Unknown title"));
    bookmark->setText(1, xml.attributes().value(hrefAttribute()).toString());

    while (xml.readNextStartElement())
    {
        if (xml.name() == QLatin1String("title")) { readTitle(bookmark); }
        else                                      { xml.skipCurrentElement(); }
    }
}
/*****************************************************************************/
/**
 * @brief XbelTreeReader::createChildItem
 * @param item
 * @return
 */
QTreeWidgetItem *XbelTreeReader::createChildItem(QTreeWidgetItem *item)
{
    QTreeWidgetItem *childItem;
    if (item)  { childItem = new QTreeWidgetItem(item); }
    else       { childItem = new QTreeWidgetItem(treeWidget); }
    childItem->setData(0, Qt::UserRole, xml.name().toString());
    return childItem;
}
/******************************* End of File *********************************/
