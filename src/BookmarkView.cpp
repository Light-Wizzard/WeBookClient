#include "BookmarkView.h"
/*****************************************************************************/
/**
 * @brief BookmarkView::BookmarkView
 * @param parent
 */
BookmarkView::BookmarkView(QWidget *parent) : QWidget(parent)
{
    formLayout = new QFormLayout(this);
    formLayout->setObjectName(QString::fromUtf8("formLayout"));
    labelTitle = new QLabel(this);
    labelTitle->setObjectName(QString::fromUtf8("labelTitle"));

    formLayout->setWidget(1, QFormLayout::LabelRole, labelTitle);

    lineEditTitle = new QLineEdit(this);
    lineEditTitle->setObjectName(QString::fromUtf8("lineEditTitle"));

    formLayout->setWidget(1, QFormLayout::FieldRole, lineEditTitle);

    labelUrl = new QLabel(this);
    labelUrl->setObjectName(QString::fromUtf8("labelUrl"));

    formLayout->setWidget(2, QFormLayout::LabelRole, labelUrl);

    lineEditUrl = new QLineEdit(this);
    lineEditUrl->setObjectName(QString::fromUtf8("lineEditUrl"));

    formLayout->setWidget(2, QFormLayout::FieldRole, lineEditUrl);

    labelOptions = new QLabel(this);
    labelOptions->setObjectName(QString::fromUtf8("labelOptions"));

    formLayout->setWidget(3, QFormLayout::LabelRole, labelOptions);

    horizontalLayoutOptions = new QHBoxLayout(this);
    horizontalLayoutOptions->setObjectName(QString::fromUtf8("horizontalLayoutOptions"));
    pushButtonAdd = new QPushButton(this);
    pushButtonAdd->setObjectName(QString::fromUtf8("pushButtonAdd"));
    horizontalLayoutOptions->addWidget(pushButtonAdd);
    horizontalSpacerOptions = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayoutOptions->addItem(horizontalSpacerOptions);
    formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayoutOptions);
    labelPlaceholderTree = new QLabel(this);
    labelPlaceholderTree->setObjectName(QString::fromUtf8("labelPlaceholderTree"));
    formLayout->setWidget(0, QFormLayout::LabelRole, labelPlaceholderTree);
    treeWidget = new TreeWidgetView();
    treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
    //treeWidget->setColumnCount(0);

    formLayout->setWidget(0, QFormLayout::FieldRole, treeWidget);
    // Signals
    connect(pushButtonAdd, &QPushButton::clicked, this, &BookmarkView::addBookmark);

    QTimer::singleShot(200, this, &BookmarkView::createPage);
}
/*****************************************************************************/
/**
 * @brief BookmarkView::addBookmark
 */
void BookmarkView::addBookmark()
{
    treeWidget->setTitle(lineEditTitle->text());
    treeWidget->setUrl(lineEditUrl->text());
    treeWidget->addBookmark();
}
/*****************************************************************************/
/**
 * @brief BookmarkView::createPage
 */
void BookmarkView::createPage()
{
    retranslateUi(getMainWindow());
}
/*****************************************************************************/
/**
 * @brief BookmarkView::favIcon
 * @return
 */
QIcon BookmarkView::favIcon() const
{
    // FIXME icon
    static QIcon favIcon(QStringLiteral(":addressbook.png"));
    return favIcon;
}
/*****************************************************************************/
/**
 * @brief BookmarkView::retranslateUi
 * @param MainWindow
 */
void BookmarkView::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
    labelTitle->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
    labelUrl->setText(QCoreApplication::translate("MainWindow", "URL", nullptr));
    labelOptions->setText(QCoreApplication::translate("MainWindow", "Options", nullptr));
    pushButtonAdd->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
    labelPlaceholderTree->setText(QString());
} // retranslateUi
/*****************************************************************************/
/**
 * @brief BookmarkView::getMainWindow
 * @return
 */
QMainWindow *BookmarkView::getMainWindow()
{
    foreach (QWidget *w, qApp->topLevelWidgets())
    {
        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w)) { return mainWin; }
    }
    return nullptr;
}
/*****************************************************************************/
/**
 * @brief BookmarkView::setTitle
 * @param thisTile
 */
void BookmarkView::setTitle(const QString &thisTile)
{
    lineEditTitle->setText(thisTile);
}
/*****************************************************************************/
/**
 * @brief BookmarkView::setUrl
 * @param thisUrl
 */
void BookmarkView::setUrl(const QString &thisUrl)
{
    lineEditUrl->setText(thisUrl);
}
/******************************* End of File *********************************/
