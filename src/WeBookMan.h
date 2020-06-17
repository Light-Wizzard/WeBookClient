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

#include "QLogger/QLoggerCommon.h"

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
        QObject                 *myParent         = nullptr;    // Needed by QRegExpValidator
        QStringList              stringList;                    //
        QLogger::QLoggerCommon  *qLoggerCommon    = nullptr;    // Logging and QtSettings
        QString                  weBookListItemsReturned;       //
        QList<QVariant>          rootData          = { "ID" };  //
        bool                     isDebugMessage    = true;      // Set to true to show debug messages
        bool                     isDebugAllMessage = false;     // Set to true to show all debug messages
}; // end class WeBookMan
//#endif // WEBOOKMAN_H
/* **************************   End of File ****************************   */
