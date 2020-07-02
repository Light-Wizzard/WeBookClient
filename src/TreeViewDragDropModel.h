/******************************************************************************
* WeBook is Pronounced Web-Book, it is a Web-Book Content Managment System   *
* Drag & Drop Model                                                          *
*******************************************************************************/
#pragma once
#ifndef DRAGDROPMODEL_H
#define DRAGDROPMODEL_H
#include <QStringList>
#include <QtGui>

#include "WeBookSettings.h"

#include "TreeModel.h"

/******************************************************************************
* class TreeViewDragDropModel                                                 *
*******************************************************************************/
class TreeViewDragDropModel : public TreeModel
{
        Q_OBJECT

    public:
        explicit TreeViewDragDropModel(const QString &strings, QObject *parent = nullptr);

        Qt::ItemFlags   flags(const QModelIndex &index) const;
        bool            dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
        QMimeData      *mimeData(const QModelIndexList &indexes) const;
        QStringList     mimeTypes() const;
        Qt::DropActions supportedDropActions() const;
        QString getErrorMessage();

    private:
        WeBookSettings          *weBookSettings      = nullptr;          //!< \c weBookSettings     \brief QtSettings
        QString                  myErrorMessage      = "";               //!< \c myErrorMessage     \brief my Error Message
        const QStringList        types               = { "text/plain" }; //!< \c types              \brief This only supports this type so make it const
        bool                     isDebugMessage      = true;             //!< \c isDebugMessage     \brief Set to true to show debug messages
        bool                     isDebugAllMessage   = false;            //!< \c isDebugAllMessage  \brief Set to true to show all debug messages
};
#endif
/******************************* End of File *********************************/


