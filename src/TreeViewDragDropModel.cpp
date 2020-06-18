/******************************************************************************
* WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
* Drag & Drop Model                                                          *
*******************************************************************************/
#include "TreeViewDragDropModel.h"
/******************************************************************************
* TreeViewDragDropModel Constructor                                           *
* Passes strings to TreeModel                                                 *
*******************************************************************************/
/*!
   \class TreeViewDragDropModel
   \fn TreeViewDragDropModel::TreeViewDragDropModel(const QString &strings, QObject *parent) : TreeModel(strings, parent)
   \brief Drag & Drop Tree View Model.
   \c strings are like database enteries, \c parent of object.
 */
TreeViewDragDropModel::TreeViewDragDropModel(const QString &strings, QObject *parent) : TreeModel(strings, parent)
{
    qLoggerCommon = new QLogger::QLoggerCommon(true);

    #ifndef QT_DEBUG
        isDebugMessage = isDebugAllMessage = false;
    #endif
    if (isDebugMessage) qDebug() << "TreeViewDragDropModel::TreeViewDragDropModel(" << strings << ", parent)";
} // end TreeViewDragDropModel
/******************************************************************************
* flags                                                                       *
*******************************************************************************/
Qt::ItemFlags TreeViewDragDropModel::flags(const QModelIndex &index) const
{
    if (isDebugAllMessage) qDebug() << "TreeViewDragDropModel::flags(" << index << ")";
    Qt::ItemFlags defaultFlags = TreeModel::flags(index);

    if (index.isValid()) return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else                 return Qt::ItemIsDropEnabled | defaultFlags;
} // end flags
/******************************************************************************
* getErrorMessage                                                             *
*******************************************************************************/
QString TreeViewDragDropModel::getErrorMessage()
{
    return myErrorMessage;
} // end getErrorMessage
/******************************************************************************
* dropMimeData                                                                *
*******************************************************************************/
bool TreeViewDragDropModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if (isDebugMessage) qDebug() << "TreeViewDragDropModel::dropMimeData(" << data << ", " << action << ", " << row  << ", " << column  << ", parent)";
    Q_UNUSED(column);
    if (action == Qt::IgnoreAction) return true;

    if (!data->hasFormat("text/plain")) return false;

    int beginRow;

    if (row != -1)             beginRow = row;
    else if (parent.isValid()) beginRow = 0;
    else                       beginRow = rowCount(QModelIndex());

    TreeItem *parentItem;
    if (!parent.isValid()) parentItem = rootTreeItem;
    else                   parentItem = static_cast<TreeItem*>(parent.internalPointer());

    qDebug() << "parentItem->data(0).toString()=" << parentItem->data(0).toString();
    int myLevel = forEachChildLevel(parentItem->data(0).toString(), QModelIndex());
    if (myLevel >= 6)
    {
        qDebug() << "aborting move due to myLevel=" << myLevel;
        myErrorMessage = QString("aborting move due to myLevel=%1 you cannot move beyond level 6 nor can you move root level").arg(myLevel);
        return false;
    }
    myErrorMessage = ""; // reset ErrorMessage

    QByteArray encodedData = data->data("text/plain");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QHash<qint64, QMap<int, QHash<int, QString> > > newItems;

    while (!stream.atEnd())
    {
        qint64 id;
        QString text;
        int thisRow; int thisColumn;
        stream >> id >> thisRow >> thisColumn >> text;
        newItems[id][thisRow][thisColumn] = text;
    }
    int rows = newItems.count();

    insertRows(beginRow, rows, parent);

    QMap<int, QHash<int, QString> > childItems;
    foreach (childItems, newItems.values())
    {
        QHash<int,QString> rowItems;
        foreach (rowItems, childItems.values())
        {
            foreach (int thisColumn, rowItems.keys())
            {
                QModelIndex idx = index(beginRow, thisColumn, parent);
                setData(idx, rowItems[thisColumn]);
            }
            ++beginRow;
        }
    }

    return true;
} // end dropMimeData
/******************************************************************************
* mimeData                                                                    *
*******************************************************************************/
QMimeData *TreeViewDragDropModel::mimeData(const QModelIndexList &indexes) const
{
    if (isDebugMessage) qDebug() << "TreeViewDragDropModel::mimeData(" << indexes << ")";
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    foreach (QModelIndex index, indexes)
    {
        if (index.isValid())
        {
            QString text = data(index, Qt::DisplayRole).toString();
            stream << index.internalId() << index.row() << index.column() << text;
        }
    }

    mimeData->setData("text/plain", encodedData);
    return mimeData;
} // end mimeData
/******************************************************************************
* mimeTypes                                                                   *
*******************************************************************************/
QStringList TreeViewDragDropModel::mimeTypes() const
{
    if (isDebugAllMessage) qDebug() << "TreeViewDragDropModel::mimeTypes = text/plain";
    return types;
} // end mimeTypes
/******************************************************************************
* supportedDropActions MoveAction only                                        *
*******************************************************************************/
Qt::DropActions TreeViewDragDropModel::supportedDropActions() const
{
    if (isDebugAllMessage) qDebug() << "TreeViewDragDropModel::supportedDropActions = Qt::MoveAction";
    return Qt::MoveAction;
} // end supportedDropActions
/******************************* End of File *********************************/


