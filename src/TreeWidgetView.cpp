#include "TreeWidgetView.h"

/*****************************************************************************/
/**
 * @brief TreeWidgetView::TreeWidgetView
 */
TreeWidgetView::TreeWidgetView()
{
    QStringList labels;
    labels << QObject::tr("Title") << QObject::tr("Location");
    header()->setSectionResizeMode(QHeaderView::Stretch);
    setHeaderLabels(labels);
    #if !defined(QT_NO_CONTEXTMENU) && !defined(QT_NO_CLIPBOARD)
    setContextMenuPolicy(Qt::CustomContextMenu);
    //QObject::connect(myBookmarkView, &QWidget::customContextMenuRequested, this, &Browser::onCustomContextMenuRequested);
    #endif

    setBookmarkName("bookmarks.xbel");
    searchBookmarkFile();
    if (myBookmarkFile.isEmpty())
    {
        // if it cannot find one then use the built-in one
        myBookmarkFile = ":/bookmarks.xbel";
    }
    QFile file(myBookmarkFile);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("QXmlStream Bookmarks"), tr("Cannot read file %1:\n%2.").arg(QDir::toNativeSeparators(myBookmarkFile), file.errorString()));
        return;
    }
    xmlReader = new XbelTreeReader(this);

    if (!xmlReader->read(&file))
    {
        QMessageBox::warning(this, tr("QXmlStream Bookmarks"), tr("Parse error in file %1:\n\n%2").arg(QDir::toNativeSeparators(myBookmarkFile), xmlReader->errorString()));
    }
    else
    {
        //statusBar()->showMessage(tr("File loaded"), 2000);
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::dragEnterEvent
 * @param event
 */
void TreeWidgetView::dragEnterEvent(QDragEnterEvent *event)
{
    draggedItem = currentItem();
    QTreeWidget::dragEnterEvent(event);
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::dropEvent
 * @param event
 */
void TreeWidgetView::dropEvent(QDropEvent *event)
{
    QModelIndex droppedIndex = indexAt(event->pos());

    if( !droppedIndex.isValid() ) { return; }

    if(draggedItem)
    {
        QTreeWidgetItem* dParent = draggedItem->parent();
        if(dParent)
        {
            if(itemFromIndex(droppedIndex.parent()) != dParent) { return; }
            dParent->removeChild(draggedItem);
            dParent->insertChild(droppedIndex.row(), draggedItem);
        }
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::favIcon
 * @return
 */
QIcon TreeWidgetView::favIcon() const
{
    // FIXME icon
    static QIcon favIcon(QStringLiteral(":addressbook.png"));
    return favIcon;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::searchBookmarkFile
 * @return
 */
QString TreeWidgetView::searchBookmarkFile()
{
    //QString theAppDataLocation = getAppDataLocation();
    // Relative to Bin Dir
    QString theBinDir = QCoreApplication::applicationDirPath();
    QString theFileName = getBookmarkName();
    QStringList theSearchList;
    theSearchList.append(theBinDir);
    theSearchList.append(theBinDir + "/" + getBookmarkFolder());
    theSearchList.append(theBinDir + "/../" + getBookmarkFolder());
    theSearchList.append(theBinDir + QString("%1%2%3%4").arg(QDir::separator(), QCoreApplication::applicationName(), QDir::separator(), getBookmarkFolder())); // for development with shadow build (Linux)
    theSearchList.append(theBinDir + QString("/../%1/%2").arg(QCoreApplication::applicationName(), getBookmarkFolder())); // for development with shadow build (Linux)
    theSearchList.append(theBinDir + QString("/../../%1/%2").arg(QCoreApplication::applicationName(), getBookmarkFolder())); // for development with shadow build (Windows)
    theSearchList.append(QDir::rootPath() + getBookmarkFolder() + "/opt");
    theSearchList.append(QDir::rootPath() + getBookmarkFolder());
    //
    foreach (QString thisDir, theSearchList)
    {
        QFile theBookmarkFile(thisDir + QDir::separator() + theFileName);
        if (theBookmarkFile.exists())
        {
            theFileName = QDir(theBookmarkFile.fileName()).canonicalPath();
            QFileInfo myFileInfo(theFileName);
            theFileName = myFileInfo.absoluteFilePath();
            setBookmarkFile(theFileName);
            setBookmarkPath(myFileInfo.absolutePath());
            qDebug() << QString("%1: %2").arg(QObject::tr("Using Bookmark file"), qPrintable(theFileName));
            return theFileName;
        }
    }
    // not found, check main theAppName and folder should be the same
    foreach (QString thisDir, theSearchList)
    {
        qWarning() << QString("%1: %2/%3").arg(QObject::tr("not found"), thisDir, theFileName);
    }
    qFatal("%s", qPrintable(QString("%1: %2").arg(QObject::tr("Cannot find Bookmark file"), theFileName)));
    return nullptr;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setBookmarkFile
 * @param thisBookmarkFile
 */
void TreeWidgetView::setBookmarkFile(const QString &thisBookmarkFile)
{
    if (myBookmarkFile != thisBookmarkFile)
    {
        myBookmarkFile = thisBookmarkFile;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getBookmarkFile
 * @return
 */
QString TreeWidgetView::getBookmarkFile()
{
    return myBookmarkFile;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setBookmarkPath
 * @param thisBookmarkPath
 */
void TreeWidgetView::setBookmarkPath(const QString &thisBookmarkPath)
{
    if (myBookmarkPath != thisBookmarkPath)
    {
        myBookmarkPath = thisBookmarkPath;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getBookmarkPath
 * @return
 */
QString TreeWidgetView::getBookmarkPath()
{
    return myBookmarkPath;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setBookmarkFolder
 * @param thisBookmarkFolder
 */
void TreeWidgetView::setBookmarkFolder(const QString &thisBookmarkFolder)
{
    if (myBookmarkFolder != thisBookmarkFolder)
    {
        myBookmarkFolder = thisBookmarkFolder;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getBookmarkFolder
 * @return
 */
QString TreeWidgetView::getBookmarkFolder()
{
    return myBookmarkFolder;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setBookmarkName
 * @param thisBookmarkName
 */
void TreeWidgetView::setBookmarkName(const QString &thisBookmarkName)
{
    if (myBookmarkName != thisBookmarkName)
    {
        myBookmarkName = thisBookmarkName;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getBookmarkFileName
 * @return
 */
QString TreeWidgetView::getBookmarkName()
{
    return myBookmarkName;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::addTreeRoot
 * @param theTitle
 * @param theUrl
 */
void TreeWidgetView::addTreeRoot(QString theTitle, QString theUrl)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(this);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, theTitle);
    treeItem->setText(1, theUrl);
    addTreeChild(treeItem, theTitle + "A", "Child_first");
    //addTreeChild(treeItem, theTitle + "B", "Child_second");
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setTitle
 * @param thisTitle
 */
void TreeWidgetView::setTitle(const QString &thisTitle)
{
    if (myTitle != thisTitle)
    {
        myTitle = thisTitle;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getTitle
 * @return
 */
QString TreeWidgetView::getTitle()
{
    return myTitle;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::setUrl
 * @param thisUrl
 */
void TreeWidgetView::setUrl(const QString &thisUrl)
{
    if (myUrl != thisUrl)
    {
        myUrl = thisUrl;
    }
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::getUrl
 * @return
 */
QString TreeWidgetView::getUrl()
{
    return myUrl;
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::addTreeChild
 * @param parent
 * @param theTitle
 * @param theUrl
 */
void TreeWidgetView::addTreeChild(QTreeWidgetItem *parent, QString theTitle, QString theUrl)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, theTitle);
    treeItem->setText(1, theUrl);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::addBookmark
 * @param thisUrl
 */
void TreeWidgetView::addBookmark()
{
    qDebug() << "Bookmark";
    if (myTitle.isEmpty()) { return; }
    if (myUrl.isEmpty()) { return; }

    if (currentItem())
    {
        addTreeChild(currentItem(), myTitle, myUrl);
    }
    else
    {
        addTreeChild(itemAt(0,0), myTitle, myUrl);
    }
    save();
}
/*****************************************************************************/
/**
 * @brief TreeWidgetView::save
 */
void TreeWidgetView::save()
{
    QFile file(myBookmarkFile);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("QXmlStream Bookmarks"), tr("Cannot write file %1:\n%2.").arg(QDir::toNativeSeparators(myBookmarkFile), file.errorString()));
        return;
    }
    XbelWriter writer(this);
    if (writer.writeFile(&file))
    {
        // FIXME
        //statusBar()->showMessage(tr("File saved"), 2000);
    }
}
/******************************* End of File *********************************/
