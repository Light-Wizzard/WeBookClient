/******************************************************************************
* WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#include "MainWindow.h"

/******************************************************************************
* \fn void mainEventHandler(int eventValue)                                   *
* \brief main Event Handler.
*******************************************************************************/
void mainEventHandler(int eventValue)
{
    switch (eventValue)
    {
        case 0: // Close
            //if (myLogFileHandle.isOpen()) myLogFileHandle.close();
            break;
        default:
            break;
    }
} // end mainEventHandler
/******************************************************************************
* \fn int main(int argc, char *argv[])                                        *
* \breif This is a Qt GUI Application written to be a Conent Manager          *
* The concept is WeBook, or Web Book, meaning it can manage my Web Conent.    *
* The WeBookClient concept is based on a fully integrated system.             *
* I use QSettings, and Qt for that matter, so I try to set things up right    *
* Settings that the Application requires:                                     *
* iniFileName: settings.ini, sounds simple if everyone wanted to call it that *
* I do not like hard coding things that should not be, but it is required     *
* applicationName                                                             *
* organizationName                                                            *
* organizationDomain                                                          *
* https://doc.qt.io/qt-5/qstandardpaths.html                                  *
* CryptoKey and CryptoIvVector are passed in from Command Line for Security   *
* If you change these once in use, you will have to reset all the Passwords   *
* Never use the Defaults ConstDefaultCryptoKey/ConstDefaultCryptoIvVector     *
* These are only for testing, and for an example                              *
*******************************************************************************/
int main(int argc, char *argv[])
{
    // Load Resource File WeBookClient.qrc
    Q_INIT_RESOURCE(WeBookClient);
    QApplication app(argc, argv);
    MainWindow *weBookWindow = new MainWindow();
    QObject::connect(weBookWindow, &MainWindow::handleEventAction, mainEventHandler);
    weBookWindow->show();
    return app.exec();
} // end main
/******************************* End of File *********************************/

