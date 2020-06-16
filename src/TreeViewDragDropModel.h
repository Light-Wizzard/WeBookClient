/******************************************************************************
** WeBook is Pronounced Web-Book, it is a Web-Book Content Managment System   *
** Drag & Drop Model                                                          *
*******************************************************************************/
#pragma once
#ifndef DRAGDROPMODEL_H
#define DRAGDROPMODEL_H
#include <QStringList>
#include <QtGui>

#include "QLogger/QLoggerCommon.h"

#include "TreeModel.h"

/******************************************************************************
** class TreeViewDragDropModel                                                *
*******************************************************************************/
class TreeViewDragDropModel : public TreeModel
{
        Q_OBJECT

    public:
        explicit TreeViewDragDropModel(const QString &strings, QObject *parent = 0);

        Qt::ItemFlags   flags(const QModelIndex &index) const;
        bool            dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        QMimeData      *mimeData(const QModelIndexList &indexes) const;
        QStringList     mimeTypes() const;
        Qt::DropActions supportedDropActions() const;
        QString getErrorMessage();

    private:
        QLogger::QLoggerCommon  *qLoggerCommon       = nullptr;          // Logging and QtSettings
        QString                  myErrorMessage      = "";               // my Error Message
        const QStringList        types               = { "text/plain" }; // This only supports this type so make it const
        bool                     isDebugMessage      = true;             // Set to true to show debug messages
        bool                     isDebugAllMessage   = false;            // Set to true to show all debug messages
};
#endif
/* ***************************** End of File ******************************* */

