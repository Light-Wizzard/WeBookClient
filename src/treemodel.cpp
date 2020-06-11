/******************************************************************************
** WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
** Drag & Drop Model                                                          *
*******************************************************************************/
#include "treemodel.h"
/******************************************************************************
** TreeModel Constructor                                                      *
** The QModelIndex class is used to locate data in a data model.              *
*******************************************************************************/
TreeModel::TreeModel(const QString &strings, QObject *parent) : QAbstractItemModel(parent)
{
    weBookCommon = new WeBookCommon(true);

    #ifndef QT_DEBUG
        isDebugMessage = isDebugAllMessage = false;
    #endif
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::TreeModel(" << strings << ", parent)";

    myParent = parent;

    rootTreeItem = new TreeItem(rootData, 0); // Header

    setupModelData(strings.split('\n'), rootTreeItem);

} // end TreeModel
/******************************************************************************
** TreeModel Deconstructor                                                    *
*******************************************************************************/
TreeModel::~TreeModel()
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::~TreeModel";
    delete rootTreeItem;
} // end ~TreeModel
/******************************************************************************
** setupModelData(const QStringList &lines, TreeItem *parent)                 *
** lines is from bookListItems in mainwindow constructor                      *
*******************************************************************************/
void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::setupModelData(" << lines << ", parent)";
    QList<TreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;
    // Given a QStringList get its count
    while (number < lines.count())
    {
        int position = 0;
        // if position is less than length of current line
        while (position < lines[number].length())
        {
            // If first position 0 first letter is a space, its a child, and the next letter is also a space
            // So position should = 2 if a child
            if (lines[number].mid(position, 1) != " ") break;
            position++;
        }
        // we want just the string without the padding if a child
        QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty())
        {
            // Read the column data from the rest of the line.
            // Tab (\t) is used to delimit columns
            QStringList columnStrings = lineData.split("\t", Qt::SkipEmptyParts);
            QList<QVariant> columnData;
            for (int column = 0; column < columnStrings.count(); ++column) columnData << columnStrings[column];
            // Indentaion means its a child
            if (position > indentations.last())
            {
                // The last child of the current parent is now the new parent unless the current parent has no children.
                if (parents.last()->childCount() > 0)
                {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            }
            else
            {
                while (position < indentations.last() && parents.count() > 0)
                {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }
            int level = -1;
            switch (position)
            {
                case 0:  level = 0; break;
                case 2:  level = 1; break;
                case 4:  level = 2; break;
                case 6:  level = 3; break;
                case 8:  level = 4; break;
                case 10: level = 5; break;
                case 12: level = 6; break;
            }
            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, level, parents.last()));
        }

        number++;
    }
} // end setupModelData
/******************************************************************************
** getSpace(int level)                                                        *
*******************************************************************************/
QString TreeModel::getSpace(int level)
{
    switch(level)
    {
        case 0: return "";              // 0  H1
        case 1: return "  ";            // 2  H2
        case 2: return "    ";          // 4  H3
        case 3: return "      ";        // 6  H4
        case 4: return "        ";      // 8  H5
        case 5: return "          ";    // 10 H6
    }
    return "";
} // end getSpace
/******************************************************************************
** forEach                                                                    *
** 1. Clear QStringList: treeListItemsReturned.clear();                       *
** 2. Call on root: forEach(QModelIndex(), false);                            *
** 3. forEach is initally set to false, and set to true in hasChilren iterator*
** 4. Depending on isChild, format the values                                 *
*******************************************************************************/
void TreeModel::forEachSave(const QModelIndex &parent, bool isChild)
{
    static int recursiveLevel = -1; recursiveLevel++; // Level is at 0 first call
    //
    QModelIndex MyIndex;
    QString cellOne;
    QString cellTwo;
    // by calling row and column Count with parent,
    // we are assured to get tree model in top to bottom, with children order
    for(int myRow = 0; myRow < rowCount(parent); ++myRow)
    {
        for (int myCol = 0; myCol < columnCount(parent); ++myCol)
        {
            // This is designed to have two colomns: title and description, check last
            if (myCol == 0)
            {
                MyIndex = index(myRow, myCol, parent);
                cellOne = data(MyIndex, Qt::DisplayPropertyRole).toString();
            }
            else
            {
                // This is the last Column
                MyIndex = index(myRow, myCol, parent);
                cellTwo = data(MyIndex, Qt::DisplayPropertyRole).toString();
                if (isChild)
                {
                    // Children off of Root level: Indent by 2 Spaces and seperate columns with Tab (\t) and newline (\n)
                    treeListItemsReturned.append(QString("%1%2\t%3\n").arg(getSpace(recursiveLevel)).arg(cellOne).arg(cellTwo));
                    if (isDebugMessage) QLOG_DEBUG() << "Child name=" << QString("%1%2\t%3\n").arg(getSpace(recursiveLevel)).arg(cellOne).arg(cellTwo) << " level = " << recursiveLevel;
                }
                else
                {
                    // Root Level: seperate columns with Tab (\t) and newline (\n)
                    treeListItemsReturned.append(QString("%1\t%2\n").arg(cellOne).arg(cellTwo));
                    if (isDebugAllMessage) QLOG_DEBUG() << "name=" << QString("%1\t%2\n").arg(cellOne).arg(cellTwo);
                }
                if( hasChildren(MyIndex) ) { forEachSave(MyIndex, true); recursiveLevel--; } // Sets isChild to true and iterates its Siblings
            } // end if (myCol
        } // end for (int myCol
    } // end for(int myRow
} // end forEach
/******************************************************************************
** forEachChildLevel                                                          *
** forEachChildLevel("ColumnID", QModelIndex());                              *
*******************************************************************************/
int TreeModel::forEachChildLevel(const QString &thisColId, const QModelIndex &parent)
{
    static int recursiveLevel = -1; recursiveLevel++; // Level is at 0 first call
    static int myLevel = -1;
    static QString lastLookUp = "";
    if (lastLookUp != thisColId)
    {
        lastLookUp = thisColId;
        recursiveLevel = 0; // Normally its set to -1 then incremented++ to = 0
        myLevel = -1;       // reset to -1
    }
    //
    QModelIndex MyIndex;
    QString cellOne;
    // by calling row and column Count with parent,
    // we are assured to get tree model in top to bottom, with children order
    for(int myRow = 0; myRow < rowCount(parent); ++myRow)
    {
        if (myLevel != -1) break;
        for (int myCol = 0; myCol < columnCount(parent); ++myCol)
        {
            if (myLevel != -1) break;
            // This is designed to have two colomns: title and description, check last
            if (myCol == 0)
            {
                MyIndex = index(myRow, myCol, parent);
                cellOne = data(MyIndex, Qt::DisplayPropertyRole).toString();
            }
            else
            {
                if (cellOne == thisColId)
                {
                    myLevel = recursiveLevel;
                    break;
                }
                if( hasChildren(MyIndex) ) { forEachChildLevel(thisColId, MyIndex); recursiveLevel--; } // Sets isChild to true and iterates its Siblings
            } // end if (myCol
        } // end for (int myCol
    } // end for(int myRow
    return myLevel;
} // end forEachChildLevel
/******************************************************************************
** setActive                                                                  *
** setActive("ColumnID", QModelIndex());                                      *
*******************************************************************************/
QModelIndex TreeModel::setActive(const QString &thisColId, const QModelIndex &parent)
{
    static int recursiveLevel = -1; recursiveLevel++; // Level is at 0 first call
    static int myLevel = -1;
    static QString lastLookUp = "";
    static QModelIndex makeActiveIndex;
    if (lastLookUp != thisColId)
    {
        lastLookUp = thisColId;
        recursiveLevel = 0; // Normally its set to -1 then incremented++ to = 0
        myLevel = -1;       // reset to -1
    }
    //
    QModelIndex MyIndex;
    QString cellOne;
    // by calling row and column Count with parent,
    // we are assured to get tree model in top to bottom, with children order
    for(int myRow = 0; myRow < rowCount(parent); ++myRow)
    {
        if (myLevel != -1) break;
        for (int myCol = 0; myCol < columnCount(parent); ++myCol)
        {
            if (myLevel != -1) break;
            // This is designed to have two colomns: title and description, check last
            if (myCol == 0)
            {
                MyIndex = index(myRow, myCol, parent); // myCol == 0
                cellOne = data(MyIndex, Qt::DisplayPropertyRole).toString();
            }
            else
            {
                if (cellOne == thisColId)
                {
                    myLevel = recursiveLevel; // Now myLevel is changed from -1 to this value; breaking out of recursive Levels
                    makeActiveIndex = MyIndex;
                    break;
                }
                if( hasChildren(MyIndex) ) { forEachChildLevel(thisColId, MyIndex); recursiveLevel--; } // Sets isChild to true and iterates its Siblings
            } // end if (myCol
        } // end for (int myCol
    } // end for(int myRow
    return makeActiveIndex;
} // end setActive
/******************************************************************************
** getData returns treeListItemsReturned                                      *
*******************************************************************************/
QString TreeModel::getData()
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::getData";
    treeListItemsReturned.clear();
    forEachSave(QModelIndex(), false);
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::getData()=" << treeListItemsReturned;
    return treeListItemsReturned;
} // end getData
/******************************************************************************
** index(int row, int column, const QModelIndex &parent)                      *
*******************************************************************************/
QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::index(" << row << "," << column << ", parent)";
    TreeItem *parentItem;

    if (!parent.isValid()) parentItem = rootTreeItem;
    else                   parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem) return createIndex(row, column, childItem);
    else           return QModelIndex();
} // end index
/******************************************************************************
** parent(const QModelIndex &index)                                           *
*******************************************************************************/
QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::parent(" << index << ")";
    if (!index.isValid()) return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootTreeItem) return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
} // end parent
/******************************************************************************
** data(const QModelIndex &index, int role)                                   *
*******************************************************************************/
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::data(" << index << ", " << role << ")";
    if (!index.isValid()) return QVariant();

    if (role == Qt::DisplayPropertyRole)
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        return item->data(index.column());
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole) return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
} // end data
/******************************************************************************
** headerData(int section, Qt::Orientation orientation, int role)             *
*******************************************************************************/
QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::headerData(" << section << "," << orientation << "," << role << ")";
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) return rootTreeItem->data(section);

    return QVariant();
} // end headerData
/******************************************************************************
** setData(const QModelIndex &index, const QVariant &value, int role)         *
*******************************************************************************/
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::setData(" << index << ", " << value << role << ")";


    if (!index.isValid() || role != Qt::EditRole) return false;

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());


    if(role == Qt::EditRole && index.column() == 0)
    {
        QRegExpValidator rxv(QRegExp("^[a-zA-Z0-9_.-]*$"), myParent);
        int pos = 0;
        QString tmp = value.toString();
        if(rxv.validate(tmp, pos) != QValidator::Acceptable) { return false; }
    }

    if (item->setData(index.column(), value)) emit dataChanged(index, index);
    else                                      return false;

    return true;
} // end setData
/******************************************************************************
** flags(const QModelIndex &index)                                            *
*******************************************************************************/
Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::flags(" << index << ")";
    if (!index.isValid()) return Qt::ItemIsEnabled | Qt::NoItemFlags;
    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable | QAbstractItemModel::flags(index);
} // end flags
/******************************************************************************
** columnCount(const QModelIndex &parent)                                     *
*******************************************************************************/
int TreeModel::columnCount(const QModelIndex &parent) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::columnCount(parent)";
    if (parent.isValid()) return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else                  return rootTreeItem->columnCount();
} // end columnCount
/******************************************************************************
** insertRows(int position, int rows, const QModelIndex &parent)              *
*******************************************************************************/
bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::insertRows(" << position << "," << rows << ", parent)";

    TreeItem *parentItem;

    if (!parent.isValid()) parentItem = rootTreeItem;
    else                   parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (position < 0 || position > parentItem->childCount()) return false;

    QList<QVariant> blankList;
    for (int column = 0; column < columnCount(); ++column) blankList << QVariant("");



    int myLevel = forEachChildLevel(parentItem->data(0).toString(), QModelIndex());
    QLOG_DEBUG() << "myLevel=" << myLevel;

    beginInsertRows(parent, position, position + rows - 1);
    for (int row = 0; row < rows; ++row)
    {
        TreeItem *newItem = new TreeItem(blankList, myLevel, parentItem);
        if (!parentItem->insertChild(position, newItem)) break;
    }
    endInsertRows();
    return true;
} // end insertRows
/******************************************************************************
** removeRows(int position, int rows, const QModelIndex &parent)              *
*******************************************************************************/
bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    if (isDebugMessage) QLOG_DEBUG() << "TreeModel::removeRows(" << position << "," << rows << ", parent)";
    TreeItem *parentItem;

    if (!parent.isValid()) parentItem = rootTreeItem;
    else                   parentItem = static_cast<TreeItem*>(parent.internalPointer());

    if (position < 0 || position > parentItem->childCount()) return false;

    beginRemoveRows(parent, position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
    {
        if (!parentItem->removeChild(position)) break;
    }

    endRemoveRows();
    return true;
} // end removeRows
/******************************************************************************
** rowCount(const QModelIndex &parent)                                        *
*******************************************************************************/
int TreeModel::rowCount(const QModelIndex &parent) const
{
    if (isDebugAllMessage) QLOG_DEBUG() << "TreeModel::rowCount(parent)";
    TreeItem *parentItem;

    if (!parent.isValid()) parentItem = rootTreeItem;
    else                   parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
} // end rowCount
/* ***************************** End of File ******************************* */

