/******************************************************************************
** WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#include "MainWindow.h"

//static QFile myLogFileHandle;
//static QString myLogPathFileName = "WeBookClient.log";
//static QString myAppName = "WeBookClient";
//static bool isLogToFile = true;
//static bool isRunOnce = false;
/******************************************************************************
** mainEventHandler                                                           *
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
** WeBookMessenger                                                            *
** This uses Qt qInstallMessageHandler(WeBookMessenger);                      *
** I have no idea if this gets called in a Thread, but Qt should handle it,   *
** ensuring thread safe way to open and write to a log file.                  *
** Note: I close the file in mainEventHandler.                                *
*******************************************************************************/
//void WeBookMessenger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
//{
//    QHash<QtMsgType, QString> msgLevelHash({{QtDebugMsg, "Debug"}, {QtInfoMsg, "Info"}, {QtWarningMsg, "Warning"}, {QtCriticalMsg, "Critical"}, {QtFatalMsg, "Fatal"}});
//    QString txt = QString("%1 %2: %3 (%4:%5, %6)").arg(QTime::currentTime().toString("hh:mm:ss.zzz")).arg(msgLevelHash[type]).arg(msg).arg(context.file).arg(context.line).arg(context.function);
//    if (isLogToFile)
//    {
//        if (!isRunOnce)
//        {
//            isRunOnce = true;
//            QLogger::myLogFile = QString("%1%2%3.log").arg(myLogPathFileName).arg(QDir::separator()).arg(myAppName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
//            QLogger::myModule = "WeBookClient";
//            QLogger::QLoggerManager *manager = QLogger::QLoggerManager::getInstance();
//            manager->addDestination(QLogger::myLogFile, QLogger::myModule, QLogger::LogLevel::Debug);
//        }
//        QLOG_DEBUG() << txt;
//        //        if (!myLogFileHandle.isOpen())
//        //        {
//        //            myLogFileHandle.setFileName(myLogPathFileName);
//        //            myLogFileHandle.open(QIODevice::WriteOnly | QIODevice::Append);
//        //        }
//        //        QTextStream ts(&myLogFileHandle);
//        //        ts << txt << endl;
//    }
//    else
//    {
//        QByteArray formattedMessage = txt.toLocal8Bit();
//        fprintf(stderr, "%s\n", formattedMessage.constData());
//        fflush(stderr);
//    }
//    if (type == QtFatalMsg) abort();
//} // end
/******************************************************************************
** main                                                                       *
** This is a Qt GUI Application written to be a Conent Manager                *
** The concept is WeBook, or Web Book, meaning it can manage my Web Conent    *
** The WeBookClient concept is based on a fully integrated system             *
** I use QSettings, and Qt for that matter, so I try to set things up right   *
** Settings that the Application requires:                                    *
** iniFileName: settings.ini, sounds simple if everyone wanted to call it that*
** I do not like hard coding things that should not be, but it is required    *
** applicationName                                                            *
** organizationName                                                           *
** organizationDomain                                                         *
** https://doc.qt.io/qt-5/qstandardpaths.html                                 *
** CryptoKey and CryptoIvVector are passed in from Command Line for Security  *
** If you change these once in use, you will have to reset all the Passwords  *
** Never use the Defaults ConstDefaultCryptoKey/ConstDefaultCryptoIvVector    *
** These are only for testing, and for an example                             *
*******************************************************************************/
int main(int argc, char *argv[])
{
    // Load Resource File WeBookClient.qrc
    Q_INIT_RESOURCE(WeBookClient);
    QApplication app(argc, argv);
    // WeBook Common has QtSettings and Crypto Functions Common between Client/Server
    QLogger::QLoggerCommon *qLoggerCommon = new QLogger::QLoggerCommon(false);
    QLoggerCrypto *weBookCrypto = new QLoggerCrypto();
    QString applicationName;
    //#define USE_REAL_FILENAME
    #ifdef USE_REAL_FILENAME
        applicationName = QFileInfo(QApplication::applicationFilePath()).fileName();
        if (applicationName.isEmpty()) applicationName = qLoggerCommon->getAppName(); // This can happen in compile envirnoment
    #else
        applicationName    = qLoggerCommon->getAppName();
    #endif
    // From *.pro file TARGET   = WeBook, maybe getTarget?
    QApplication::setWindowIcon(QIcon(":/images/logo32.png"));
    QCommandLineParser parser;
    QApplication::setApplicationVersion(QT_VERSION_STR);
    parser.setApplicationDescription(QApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    // a b c d f i k l n p
    QCommandLineOption a_opt({"a","appname"},       QApplication::translate("main", "Application Name if you want it different then executable name."), "appname");
    QCommandLineOption b_opt({"b","blogfolder"},    QApplication::translate("main", "The Log Folder Name: logs"), "blogfolder");
    QCommandLineOption c_opt({"c","cryptoiv"},      QApplication::translate("main", "The Crypto IV Vector String"), "cryptoiv");
    QCommandLineOption d_opt({"d","orgdomain"},     QApplication::translate("main", "The Organization Domain URL: https://github.com/USERNAME/PROJECT"), "orgdomain");
    QCommandLineOption f_opt({"f","filepath"},      QApplication::translate("main", "The Full Path to Files like ini: /path"), "filepath");
    QCommandLineOption i_opt({"i","inifile"},       QApplication::translate("main", "The Ini File Name: WeBookClient.ini"), "inifile");
    QCommandLineOption k_opt({"k","key"},           QApplication::translate("main", "The Crypto Key String"), "key");
    QCommandLineOption l_opt({"l","logpath"},       QApplication::translate("main", "The Full Path to Log Fils: /path"), "logpath");
    QCommandLineOption n_opt({"n","orgname"},       QApplication::translate("main", "The Organization Name going to be the Window Title"), "orgname");
    QCommandLineOption p_opt({"p","port"},          QApplication::translate("main", "The Port Number of Server"), "port");
    parser.addOption(a_opt);
    parser.addOption(b_opt);
    parser.addOption(c_opt);
    parser.addOption(d_opt);
    parser.addOption(f_opt);
    parser.addOption(i_opt);
    parser.addOption(k_opt);
    parser.addOption(l_opt);
    parser.addOption(n_opt);
    parser.addOption(p_opt);
    parser.process(QApplication::arguments());
    QString theAppName      = parser.value("appname");
    QString theInit         = parser.value("inifile");
    QString theOrgName      = parser.value("orgname");
    QString theOrgDomain    = parser.value("orgdomain");
    QString theCryptoKey    = parser.value("key");
    QString theCryptoIv     = parser.value("cryptoiv");
    QString thePort         = parser.value("port");
    QString theLogPath      = parser.value("logpath");
    QString theFilePath     = parser.value("filepath");
    QString theLogFolder    = parser.value("blogfolder");
    //
    if (theAppName.isEmpty())   theAppName      = applicationName;
    if (theInit.isEmpty())      theInit         = qLoggerCommon->getIniFileName();
    if (theOrgName.isEmpty())   theOrgName      = qLoggerCommon->getOrgName();
    if (theOrgDomain.isEmpty()) theOrgDomain    = qLoggerCommon->getOrgDomain();
    if (thePort.isEmpty())      thePort         = qLoggerCommon->portToString();
    if (theLogPath.isEmpty())   theLogPath      = qLoggerCommon->getLogPath();
    if (theFilePath.isEmpty())  theFilePath     = qLoggerCommon->getFilelPath();
    if (theLogFolder.isEmpty()) theLogFolder    = qLoggerCommon->getLogFolderName();
    //
    if (theCryptoKey.isEmpty()) theCryptoKey    = weBookCrypto->getCryptoKey();
    if (theCryptoIv.isEmpty())  theCryptoIv     = weBookCrypto->getCryptoIvVector();
    //
    //isLogToFile = true;
    //myLogPathFileName = QString("%1%2.log").arg(applicationName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    //MyLogFile = QString("%1%2.log").arg(applicationName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    qLoggerCommon->setAppName(theAppName);
    qLoggerCommon->setIniFileName(theInit);
    qLoggerCommon->setOrgName(theOrgName);
    qLoggerCommon->setOrgDomain(theOrgDomain);
    qLoggerCommon->setPort(thePort.toInt());
    qLoggerCommon->setLogPath(theLogPath);
    qLoggerCommon->setFilePath(theFilePath);
    qLoggerCommon->setLogFolderName(theLogFolder);
    qLoggerCommon->setLogger();
    //
    weBookCrypto->setCryptoKey(theCryptoKey);
    weBookCrypto->setCryptoIvVector(theCryptoIv);
    //
    MainWindow *weBookWindow = new MainWindow();
    QObject::connect(weBookWindow, &MainWindow::handleEventAction, mainEventHandler);
    /*
    WeBookLogger *weBookLogger = new WeBookLogger();
    if (theLogPath.isEmpty()) theLogPath = QString("%1%2.log").arg(applicationName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    weBookLogger->setLogPath(theLogPath);
    weBookLogger->onLogFileChanged();
    QObject::connect(weBookLogger, &WeBookLogger::handelLogFileChanged, &WeBookLogger::onLogFileChanged);
    */
    //qInstallMessageHandler(WeBookMessenger); // Install the Message handler
    weBookWindow->show();
    // QApplication::setStyle(QStyleFactory::create("fusion"));
    // QStyleFactory::keys= ("Windows", "Fusion")
    // QDEBUGTS << "QStyleFactory::keys=" << QStyleFactory::keys();
    return app.exec();
} // end main
/* ***************************** End of File ******************************* */
