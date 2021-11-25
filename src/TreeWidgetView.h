#ifndef TREEWIDGETVIEW_H
#define TREEWIDGETVIEW_H

#include <QCoreApplication>
#include <QGuiApplication>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDropEvent>
#include <QObject>
#include <QWidget>
#include <QIcon>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include <QHeaderView>
#include <QDesktopServices>
#include <QMenu>
#include <QMainWindow>

#include "XbelTreeReader.h"
#include "xbelwriter.h"

QT_BEGIN_NAMESPACE
class QTreeWidget;
class QTreeWidgetItem;
QT_END_NAMESPACE
/*****************************************************************************/
/**
 * @brief The TreeWidgetView class
 */
class TreeWidgetView : public QTreeWidget
{
        Q_OBJECT
    public:
        TreeWidgetView();

        QIcon favIcon() const;
        QString searchBookmarkFile();
        // Bookmark Name
        void setBookmarkName(const QString &thisBookmarkName);
        QString getBookmarkName();
        // Bookmark Folder
        void setBookmarkFolder(const QString &thisBookmarkFolder);
        QString getBookmarkFolder();
        // Bookmark File
        void setBookmarkFile(const QString &thisBookmarkFile);
        QString getBookmarkFile();
        // Bookmark Path
        void setBookmarkPath(const QString &thisBookmarkPath);
        QString getBookmarkPath();
        // Add
        void addTreeChild(QTreeWidgetItem *parent, QString theTitle, QString theUrl);
        void addTreeRoot(QString theTitle, QString theUrl);
        // Title
        void setTitle(const QString &thisTitle);
        QString getTitle();
        // Url
        void setUrl(const QString &thisUrl);
        QString getUrl();
        //
        void addBookmark();
        void save();


    protected:
        virtual void dragEnterEvent(QDragEnterEvent *event) override;
        virtual void dropEvent(QDropEvent *event) override;

    private:
        QTreeWidgetItem *draggedItem;
        QString          myBookmarkName   = ""; //!< \c myBookmarkName   @brief Bookmark Name
        QString          myBookmarkFile   = ""; //!< \c myBookmarkFile   @brief Bookmark File
        QString          myBookmarkPath   = ""; //!< \c myBookmarkPath   @brief Bookmark Path
        QString          myBookmarkFolder = ""; //!< \c myBookmarkFolder @brief Bookmark Folder
        QString          myTitle          = "";
        QString          myUrl            = "";
        XbelTreeReader  *xmlReader;

}; // end class TreeWidgetView
#endif // TREEWIDGETVIEW_H
/******************************* End of File *********************************/
