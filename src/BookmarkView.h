#ifndef BOOKMARKVIEW_H
#define BOOKMARKVIEW_H

#include <QMainWindow>
#include <QObject>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include "TreeWidgetView.h"
#include "browserwindow.h"

/*****************************************************************************/
/**
 * @brief The BookmarkView class
 */
class BookmarkView : public QWidget
{
        Q_OBJECT
    public:
        explicit BookmarkView(QWidget *parent = nullptr);

        virtual void retranslateUi(QMainWindow *MainWindow);

        QIcon favIcon() const;

        QMainWindow *getMainWindow();

        void setTitle(const QString &thisTile);
        void setUrl(const QString &thisUrl);

    public slots:
        void createPage();
        void addBookmark();

    private:
        QFormLayout     *formLayout;
        QLabel          *labelTitle;
        QLineEdit       *lineEditTitle;
        QLabel          *labelUrl;
        QLineEdit       *lineEditUrl;
        QLabel          *labelOptions;
        QHBoxLayout     *horizontalLayoutOptions;
        QPushButton     *pushButtonAdd;
        QSpacerItem     *horizontalSpacerOptions;
        QLabel          *labelPlaceholderTree;
        TreeWidgetView  *treeWidget;
}; // end class BookmarkView
#endif // BOOKMARKVIEW_H
/******************************* End of File *********************************/
