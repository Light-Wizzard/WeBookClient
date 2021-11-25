#ifndef HELPTAB_H
#define HELPTAB_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTextBrowser>
#include <QUrl>
#include <QtWidgets/QVBoxLayout>

/*****************************************************************************/
/**
 * @brief The HelpTab class
 */
class HelpTab : public QWidget
{
        Q_OBJECT
    public:
        explicit HelpTab(QWidget *parent = nullptr);

        void setPageSource(const QString &thisPageSource);
        QString getPageSource();

        QIcon favIcon() const;

    private:
        QVBoxLayout *verticalLayoutHelp;
        QTextBrowser   *myTextBrowser;
        QString         myPageSource;

}; // end class HelpTab
#endif // HELPTAB_H
/******************************* End of File *********************************/
