#include "WeBookMan.h"
/******************************************************************************
** WeBookMan Constructor                                                      *
*******************************************************************************/
WeBookMan::WeBookMan(const QStringList &strings, QObject *parent) : QAbstractListModel(parent), myParent(parent), stringList(strings)
{
    qLoggerCommon = new QLogger::QLoggerCommon(true);
    qDebug() << "WeBookMan Constructor";
} // end WeBookMan
/******************************************************************************
** forEach                                                                    *
** 1. Clear QStringList: treeListItemsReturned.clear();                       *
** 2. Call on root: forEach(QModelIndex(), false);                            *
** 3. forEach is initally set to false, and set to true in hasChilren iterator*
** 4. Depending on isChild, format the values                                 *
*******************************************************************************/
void WeBookMan::forEachSave(const QModelIndex &parent)
{
    static int recursiveLevel = -1; recursiveLevel++; // Level is at 0 first call
    //
    QModelIndex MyIndex;
    QString cellOne;
    // by calling row and column Count with parent,
    // we are assured to get tree model in top to bottom, with children order
    for(int myRow = 0; myRow < rowCount(parent); ++myRow)
    {
        // This is the only Column
        MyIndex = index(myRow, 0, parent);
        cellOne = data(MyIndex, Qt::DisplayRole).toString();
        if (cellOne.isEmpty()) { break; } // Do not allow empty lines
        else
        {
            weBookListItemsReturned.append(QString("%1\n").arg(cellOne));
            if (isDebugAllMessage) qDebug() << QString("name=%1").arg(cellOne);
        }
    } // end for(int myRow
} // end forEach
/******************************************************************************
** getData returns weBookListItemsReturned                                    *
*******************************************************************************/
QString WeBookMan::getData()
{
    if (isDebugMessage) qDebug() << "Get Data";
    weBookListItemsReturned.clear();
    forEachSave(QModelIndex());
    if (isDebugMessage) qDebug() << "TreeModel::getData()=" << weBookListItemsReturned;
    return weBookListItemsReturned;
} // end getData
/******************************************************************************
** getStringList                                                              *
*******************************************************************************/
QStringList WeBookMan::getStringList()
{
    if (isDebugMessage) qDebug() << "Get StringList";
    return stringList;
} // end getStringList
/******************************************************************************
** data(const QModelIndex &index, int role)                                   *
** Returns an appropriate value for the requested data.                       *
** If the view requests an invalid index, an invalid variant is returned.     *
** Any valid index that corresponds to a string in the list causes that string to be returned.*
*******************************************************************************/
QVariant WeBookMan::data(const QModelIndex &index, int role) const
{
    if (isDebugMessage) qDebug() << "data(index, role=" << role << ")";
    if (!index.isValid()) return QVariant();

    if (index.row() >= stringList.size()) return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) return stringList.at(index.row());
    else                                                 return QVariant();
} // end data
/******************************************************************************
** setData(const QModelIndex &index, const QVariant &value, int role)         *
*******************************************************************************/
/*!
    Changes an item in the string list, but only if the following conditions
    are met:

    * The index supplied is valid.
    * The index corresponds to an item to be shown in a view.
    * The role associated with editing text is specified.

    The dataChanged() signal is emitted if the item is changed.
*/
bool WeBookMan::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (isDebugMessage) qDebug() << "Set Data(index, value=" << value << ", role=" << role << ")";

    if (index.isValid() && role == Qt::EditRole)
    {
        QRegExpValidator rxv(QRegExp("^[a-zA-Z0-9_.-]*$"), myParent);
        int pos = 0;
        QString tmp = value.toString();
        if(rxv.validate(tmp, pos) != QValidator::Acceptable) { return false; }

        stringList.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }

    return false;
} // end setData
/******************************************************************************
** rowCount(const QModelIndex &parent)                                        *
** Returns the number of items in the string list as the number of rows in the model.
*******************************************************************************/
int WeBookMan::rowCount(const QModelIndex &parent) const
{
    if (isDebugMessage) qDebug() << "rowCount";
    Q_UNUSED(parent);
    return stringList.count();
} // end rowCount
/******************************************************************************
** headerData(int section, Qt::Orientation orientation, int role)             *
** Returns the appropriate header string depending on the orientation of the  *
** header and the section. If anything other than the display role is requested,*
** we return an invalid variant.                                              *
*******************************************************************************/
QVariant WeBookMan::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (isDebugMessage) qDebug() << "headerData";
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal) return QString("Column %1").arg(section);
    else                               return QString("Row %1").arg(section);
} // end headerData
/******************************************************************************
** flags(const QModelIndex &index)                                            *
** Returns an appropriate value for the item's flags. Valid items are enabled,*
** selectable, and editable.                                                  *
*******************************************************************************/
Qt::ItemFlags WeBookMan::flags(const QModelIndex &index) const
{
    if (isDebugMessage) qDebug() << "flags";
    if (!index.isValid()) return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
} // end flags
/******************************************************************************
** insertRows(int position, int rows, const QModelIndex &parent)              *
** Inserts a number of rows into the model at the specified position.         *
*******************************************************************************/
bool WeBookMan::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (isDebugMessage) qDebug() << "insertRows";
    Q_UNUSED(parent);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
    {
        stringList.insert(position, "");
    }

    endInsertRows();
    return true;
} // end insertRows
/******************************************************************************
** removeRows(int position, int rows, const QModelIndex &parent)              *
** Removes a number of rows from the model at the specified position.
*******************************************************************************/
bool WeBookMan::removeRows(int position, int rows, const QModelIndex &parent)
{
    if (isDebugMessage) qDebug() << "removeRows";
    Q_UNUSED(parent);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
    {
        stringList.removeAt(position);
    }

    endRemoveRows();
    return true;

} // end removeRows
/* ***************************** End of File ******************************* */
