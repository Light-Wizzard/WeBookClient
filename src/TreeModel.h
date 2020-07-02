/******************************************************************************
* WeBook is Pronounced Web-Book, it is a Web-Book Content Managment System   *
* Drag & Drop Model                                                          *
*******************************************************************************/
#pragma once
#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QtGui>
#include <QModelIndex>
#include <QVariant>

#include "WeBookSettings.h"

#include "TreeItem.h"

class TreeItem;
/******************************************************************************
* class TreeModel                                                            *
*******************************************************************************/
class TreeModel : public QAbstractItemModel
{
        Q_OBJECT

    public:
        explicit TreeModel(const QString &strings, QObject *parent = 0);
        ~TreeModel();

        Qt::ItemFlags flags(const QModelIndex &index) const;

        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
        QModelIndex parent(const QModelIndex &index) const;

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        int columnCount(const QModelIndex &parent = QModelIndex()) const;

        bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        QString getData();

        TreeItem        *rootTreeItem;          //!< \c rootTreeItem          \brief Root Tree Item.
        QString          treeListItemsReturned; //!< \c treeListItemsReturned \brief Tree List Items Returned.

        //void forEach(QAbstractItemModel* model, const QModelIndex &parent);
        void forEachSave(const QModelIndex &parent, bool isChild);
        QString getSpace(int level);

        int forEachChildLevel(const QString &thisColId, const QModelIndex &parent);
        QModelIndex setActive(const QString &thisColId, const QModelIndex &parent);

    protected:
        void setupModelData(const QStringList &lines, TreeItem *parent);

    private:
        WeBookSettings          *weBookSettings    = nullptr;            //!< \c weBookSettings     \brief QtSettings.
        QObject                 *myParent          = nullptr;            //!< \c myParent           \brief required by setData.
        QList<QVariant>          rootData          = { "ID", "Title" };  //!< \c rootData           \brief Root Data.
        bool                     isDebugMessage    = true;               //!< \c isDebugMessage     \brief Set to true to show debug messages.
        bool                     isDebugAllMessage = false;              //!< \c isDebugAllMessage  \brief Set to true to show all debug messages.
}; // end class TreeModel
#endif // TREEMODEL_H
/******************************* End of File *********************************/


