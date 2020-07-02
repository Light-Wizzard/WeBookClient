/******************************************************************************
* WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#pragma once
//#ifndef WEBOOKMAN_H
//#define WEBOOKMAN_H

#include <QAbstractListModel>
#include <QObject>
#include <QStringList>
#include <QtGui>

#include "WeBookSettings.h"

/******************************************************************************
* class WeBookMan : public QAbstractListModel                                *
*******************************************************************************/
class WeBookMan : public QAbstractListModel
{
        Q_OBJECT
    public:
        explicit WeBookMan(const QStringList &strings, QObject *parent = nullptr);

        int rowCount(const QModelIndex &parent = QModelIndex()) const;
        QVariant data(const QModelIndex &index, int role) const;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

        Qt::ItemFlags flags(const QModelIndex &index) const;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

        bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
        bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

        QStringList getStringList();
        void forEachSave(const QModelIndex &parent);
        QString getData();

    private:
        QObject                 *myParent         = nullptr;    //!< \c myParent                \brief Needed by QRegExpValidator
        QStringList              stringList;                    //!< \c stringList              \brief String List
        WeBookSettings          *weBookSettings    = nullptr;   //!< \c weBookSettings          \brief QtSettings
        QString                  weBookListItemsReturned;       //!< \c weBookListItemsReturned \brief WeBook List Items Returned
        QList<QVariant>          rootData          = { "ID" };  //!< \c rootData                \brief Root Data
        bool                     isDebugMessage    = true;      //!< \c isDebugMessage          \brief Set to true to show debug messages
        bool                     isDebugAllMessage = false;     //!< \c isDebugAllMessage       \brief Set to true to show all debug messages
}; // end class WeBookMan
//#endif // WEBOOKMAN_H
/******************************* End of File *********************************/

