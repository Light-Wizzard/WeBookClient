#include "HelpTab.h"

/*****************************************************************************/
/**
 * @brief HelpTab::HelpTab
 * @param parent
 */
HelpTab::HelpTab(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    setAttribute(Qt::WA_GroupLeader);

    verticalLayoutHelp = new QVBoxLayout(this);
    verticalLayoutHelp->setObjectName(QString::fromUtf8("verticalLayoutHelp"));
    myTextBrowser = new QTextBrowser(this);
    myTextBrowser->setObjectName(QString::fromUtf8("myTextBrowser"));

    verticalLayoutHelp->addWidget(myTextBrowser);

}
/*****************************************************************************/
/**
 * @brief HelpTab::setPageSource
 * @param thisPageSource
 */
void HelpTab::setPageSource(const QString &thisPageSource)
{
    if (myPageSource != thisPageSource)
    {
        myPageSource = thisPageSource;
        QUrl myQUrl = QUrl(thisPageSource);
        if (myQUrl.isValid())
        {
            myTextBrowser->setSource(myQUrl);
        }
    }
}
/*****************************************************************************/
/**
 * @brief HelpTab::getPageSource
 * @return
 */
QString HelpTab::getPageSource()
{
    return myPageSource;
}
/*****************************************************************************/
/**
 * @brief HelpTab::favIcon
 * @return
 */
QIcon HelpTab::favIcon() const
{
    // FIXME icon
    static QIcon favIcon(QStringLiteral(":help.png"));
    return favIcon;
}
/******************************* End of File *********************************/
