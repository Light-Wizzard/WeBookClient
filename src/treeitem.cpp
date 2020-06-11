/******************************************************************************
** WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
** Drag & Drop Model                                                          *
*******************************************************************************/
#include "treeitem.h"
/******************************************************************************
** TreeItem Constructor                                                       *
*******************************************************************************/
TreeItem::TreeItem(const QList<QVariant> &data, int myLevel, TreeItem *parent)
{
    weBookCommon = new WeBookCommon(true);

    #ifndef QT_DEBUG
        isDebugMessage = isDebugAllMessage = false;
    #endif
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::TreeItem(" << data << ", " << myLevel  << ", parent)";
    parentItem = parent;
    itemData = data;
    level = myLevel;
} // end TreeItem
/******************************************************************************
** TreeItem Deconstructor                                                     *
*******************************************************************************/
TreeItem::~TreeItem()
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::~TreeItem";
    qDeleteAll(childItems);
} // end ~TreeItem
/******************************************************************************
** parent                                                                     *
*******************************************************************************/
TreeItem *TreeItem::parent()
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::parent";
    return parentItem;
} // end parent
/******************************************************************************
** data(int column) 0 or 1                                                    *
*******************************************************************************/
QVariant TreeItem::data(int column) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::data(" << column << ")";
    return itemData.value(column);
} // end data
/******************************************************************************
** setData(int column, const QVariant &data)                                  *
*******************************************************************************/
bool TreeItem::setData(int column, const QVariant &data)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::setData(" << column << ", " << data << ")";
    if (column < 0 || column >= itemData.count()) return false;

    itemData.replace(column, data);
    return true;
} // end setData
/******************************************************************************
** appendChild(TreeItem *item)                                                *
*******************************************************************************/
void TreeItem::appendChild(TreeItem *item)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::appendChild(item)";
    childItems.append(item);
} // end appendChild
/******************************************************************************
** child(int row)                                                             *
*******************************************************************************/
TreeItem *TreeItem::child(int row)
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::child(" << row << ")";
    return childItems.value(row);
} // end child
/******************************************************************************
** childCount()                                                               *
*******************************************************************************/
int TreeItem::childCount() const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::childCount=" << childItems.count();
    return childItems.count();
} // end childCount
/******************************************************************************
** columnCount()                                                              *
*******************************************************************************/
int TreeItem::columnCount() const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::columnCount=" << itemData.count();
    return itemData.count();
} // end columnCount
/******************************************************************************
** insertChild(int row, TreeItem *item)                                       *
*******************************************************************************/
bool TreeItem::insertChild(int row, TreeItem *item)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::insertChild(" << row << ", item)";
    if (row < 0 || row > childItems.count()) return false;

    childItems.insert(row, item);
    return true;
} // end insertChild
/******************************************************************************
** removeChild(int row)                                                       *
*******************************************************************************/
bool TreeItem::removeChild(int row)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeItem::removeChild(" << row << ")";
    if (row < 0 || row >= childItems.count()) return false;

    delete childItems.takeAt(row);
    return true;
} // end removeChild
/******************************************************************************
** row                                                                        *
*******************************************************************************/
int TreeItem::row() const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeItem::row";
    if (parentItem) return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
} // end row
/* ***************************** End of File ******************************* */

