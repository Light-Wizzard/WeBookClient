/******************************************************************************
* WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
* Drag & Drop Model                                                          *
*******************************************************************************/
#include "TreeItem.h"
/******************************************************************************
* TreeItem Constructor                                                        *
*******************************************************************************/
/*!
   \class TreeItem
   \fn TreeItem::TreeItem(const QList<QVariant> &data, int myLevel, TreeItem *parent)
   \brief Represents a Tree Item, \c data is the Item, and \c parent of object.
 */
TreeItem::TreeItem(const QList<QVariant> &data, int myLevel, TreeItem *parent)
{
    qLoggerCommon = new QLogger::QLoggerCommon(true);

    #ifndef QT_DEBUG
        isDebugMessage = isDebugAllMessage = false;
    #endif
    if (isDebugMessage) qDebug() << "TreeItem::TreeItem(" << data << ", " << myLevel  << ", parent)";
    parentItem = parent;
    itemData = data;
    level = myLevel;
} // end TreeItem
/******************************************************************************
* TreeItem Deconstructor                                                      *
*******************************************************************************/
TreeItem::~TreeItem()
{
    if (isDebugMessage) qDebug() << "TreeItem::~TreeItem";
    qDeleteAll(childItems);
} // end ~TreeItem
/******************************************************************************
* parent                                                                      *
*******************************************************************************/
TreeItem *TreeItem::parent()
{
    if (isDebugAllMessage) qDebug() << "TreeItem::parent";
    return parentItem;
} // end parent
/******************************************************************************
* data(int column) 0 or 1                                                     *
*******************************************************************************/
QVariant TreeItem::data(int column) const
{
    if (isDebugAllMessage) qDebug() << "TreeItem::data(" << column << ")";
    return itemData.value(column);
} // end data
/******************************************************************************
* setData(int column, const QVariant &data)                                   *
*******************************************************************************/
bool TreeItem::setData(int column, const QVariant &data)
{
    if (isDebugMessage) qDebug() << "TreeItem::setData(" << column << ", " << data << ")";
    if (column < 0 || column >= itemData.count()) return false;

    itemData.replace(column, data);
    return true;
} // end setData
/******************************************************************************
* appendChild(TreeItem *item)                                                 *
*******************************************************************************/
void TreeItem::appendChild(TreeItem *item)
{
    if (isDebugMessage) qDebug() << "TreeItem::appendChild(item)";
    childItems.append(item);
} // end appendChild
/******************************************************************************
* child(int row)                                                              *
*******************************************************************************/
TreeItem *TreeItem::child(int row)
{
    if (isDebugAllMessage) qDebug() << "TreeItem::child(" << row << ")";
    return childItems.value(row);
} // end child
/******************************************************************************
* childCount()                                                                *
*******************************************************************************/
int TreeItem::childCount() const
{
    if (isDebugAllMessage) qDebug() << "TreeItem::childCount=" << childItems.count();
    return childItems.count();
} // end childCount
/******************************************************************************
* columnCount()                                                               *
*******************************************************************************/
int TreeItem::columnCount() const
{
    if (isDebugAllMessage) qDebug() << "TreeItem::columnCount=" << itemData.count();
    return itemData.count();
} // end columnCount
/******************************************************************************
* insertChild(int row, TreeItem *item)                                        *
*******************************************************************************/
bool TreeItem::insertChild(int row, TreeItem *item)
{
    if (isDebugMessage) qDebug() << "TreeItem::insertChild(" << row << ", item)";
    if (row < 0 || row > childItems.count()) return false;

    childItems.insert(row, item);
    return true;
} // end insertChild
/******************************************************************************
* removeChild(int row)                                                        *
*******************************************************************************/
bool TreeItem::removeChild(int row)
{
    if (isDebugMessage) qDebug() << "TreeItem::removeChild(" << row << ")";
    if (row < 0 || row >= childItems.count()) return false;

    delete childItems.takeAt(row);
    return true;
} // end removeChild
/******************************************************************************
* row                                                                         *
*******************************************************************************/
int TreeItem::row() const
{
    if (isDebugAllMessage) qDebug() << "TreeItem::row";
    if (parentItem) return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
} // end row
/******************************* End of File *********************************/


