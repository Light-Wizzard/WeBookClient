/******************************************************************************
** WeBook is Pronounced Web-Book, it is a Web-Book Content Managment System   *
** Drag & Drop Model                                                          *
*******************************************************************************/
#ifndef TREEITEM_H
#define TREEITEM_H
#include <QList>
#include <QStringList>
#include <QVariant>
#include <QtGui>

#include "QLogger/QLoggerCommon.h"

/******************************************************************************
** class TreeItem                                                             *
** Column is Tablature, you can define any number of columns                  *
** Row is the number of Column pairs                                          *
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

        int                 level             = -1;         // Level Number

    private:
        QLogger::QLoggerCommon  *qLoggerCommon     = nullptr;    // Logging and QtSettings
        QList<TreeItem*>         childItems;                     // child Items
        QList<QVariant>          itemData;                       // item Data
        TreeItem                *parentItem        = nullptr;    // parent Item
        bool                     isDebugMessage    = true;       // Set to true to show debug messages
        bool                     isDebugAllMessage = false;      // Set to true to show all debug messages

}; // end class TreeItem
#endif // TREEITEM_H
/* ***************************** End of File ******************************* */

