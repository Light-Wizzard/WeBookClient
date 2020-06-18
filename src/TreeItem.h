/******************************************************************************
* WeBook is Pronounced Web-Book, it is a Web-Book Content Managment System   *
* Drag & Drop Model                                                          *
*******************************************************************************/
#pragma once
#ifndef TREEITEM_H
#define TREEITEM_H
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QtGui>

#include "QLogger/QLoggerCommon.h"

/******************************************************************************
* class TreeItem                                                             *
* Column is Tablature, you can define any number of columns                  *
* Row is the number of Column pairs                                          *
*******************************************************************************/
class TreeItem
{
        Q_DISABLE_COPY(TreeItem)

    public:
        explicit TreeItem(const QList<QVariant> &data, int myLevel, TreeItem *parent = nullptr);
        ~TreeItem();

        void appendChild(TreeItem *child);                  //

        TreeItem *parent();                                 //
        TreeItem *child(int row);                           //

        QVariant data(int column) const;                    // 0 or 1 for a 2 column

        int childCount() const;                             //
        int columnCount() const;                            //
        int row() const;                                    //

        bool insertChild(int row, TreeItem *item);          //
        bool removeChild(int row);                          //

        bool setData(int column, const QVariant &data);     //

        int                 level             = -1;         //!< \c level \brief Level Number

    private:
        QLogger::QLoggerCommon  *qLoggerCommon     = nullptr;    //!< \c qLoggerCommon     \brief Logging and QtSettings
        QList<TreeItem*>         childItems;                     //!< \c childItems        \brief child Items
        QList<QVariant>          itemData;                       //!< \c itemData          \brief item Data
        TreeItem                *parentItem        = nullptr;    //!< \c parentItem        \brief parent Item
        bool                     isDebugMessage    = true;       //!< \c isDebugMessage    \brief Set to true to show debug messages
        bool                     isDebugAllMessage = false;      //!< \c isDebugAllMessage \brief Set to true to show all debug messages

}; // end class TreeItem
#endif // TREEITEM_H
/******************************* End of File *********************************/


