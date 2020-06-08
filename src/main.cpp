/******************************************************************************
** WeBook: Pronounced Web Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#include "mainwindow.h"

//static QFile myLogFileHandle;
//static QString myLogPathFileName = "WeBookClient.log";
//static bool isLogToFile = false;

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

//        RollingFileAppender *rollfile = new RollingFileAppender(QString("%1.log").arg(myLogPathFileName));
//        //roll every minute
//        rollfile->setDatePattern(RollingFileAppender::MonthlyRollover);
//        // logfile been retained
//        rollfile->setLogFilesLimit(0); // I think 0 or 1 will not delete logs
//        cuteLogger->registerCategoryAppender("WeBookServerID", rollfile);
//        // LOG_CERROR("WeBookServerID") << "roll every month and retain all files";
//        LOG_INFO() << txt;

//        if (!myLogFileHandle.isOpen())
//        {
//            myLogFileHandle.setFileName(myLogPathFileName);
//            myLogFileHandle.open(QIODevice::WriteOnly | QIODevice::Append);
//        }
//        QTextStream ts(&myLogFileHandle);
//        ts << txt << endl;
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
    WeBookCommon *weBookCommon = new WeBookCommon(false);
    QString applicationName;
    //#define USE_REAL_FILENAME
    #ifdef USE_REAL_FILENAME
        applicationName = QFileInfo(QApplication::applicationFilePath()).fileName();
        if (applicationName.isEmpty()) applicationName = weBookCommon->getAppName(); // This can happen in compile envirnoment
    #else
        applicationName    = weBookCommon->getAppName();
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
    QCommandLineOption c_opt({"c","cryptoiv"},      QApplication::translate("main", "The Crypto IV Vector String"), "cryptoiv");
    QCommandLineOption d_opt({"d","domain"},        QApplication::translate("main", "The Organization Domain URL: https://github.com/USERNAME/PROJECT"), "orgdomain");
    QCommandLineOption i_opt({"i","ini"},           QApplication::translate("main", "The Ini File Name: WeBookClient.ini"), "inifile");
    QCommandLineOption k_opt({"k","key"},           QApplication::translate("main", "The Crypto Key String"), "key");
    QCommandLineOption l_opt({"l","logpath"},       QApplication::translate("main", "The Full Path to Log Fils: /path"), "logpath");
    QCommandLineOption n_opt({"n","name"},          QApplication::translate("main", "The Organization Name going to be the Window Title"), "orgname");
    QCommandLineOption p_opt({"p","port"},          QApplication::translate("main", "The Port Number of Server"), "port");
    QCommandLineOption f_opt({"f","filepath"},      QApplication::translate("main", "The Full Path to Files like ini: /path"), "filepath");
    QCommandLineOption b_opt({"b","blogfolder"},    QApplication::translate("main", "The Log Folder Name: logs"), "blogfolder");
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
    if (theInit.isEmpty())      theInit         = weBookCommon->getIniFileName();
    if (theOrgName.isEmpty())   theOrgName      = weBookCommon->getOrgName();
    if (theOrgDomain.isEmpty()) theOrgDomain    = weBookCommon->getOrgDomain();
    if (theCryptoKey.isEmpty()) theCryptoKey    = weBookCommon->getCryptoKey();
    if (theCryptoIv.isEmpty())  theCryptoIv     = weBookCommon->getCryptoIvVector();
    if (thePort.isEmpty())      thePort         = weBookCommon->getPort();
    if (theLogPath.isEmpty())   theLogPath      = weBookCommon->getLogPath();
    if (theFilePath.isEmpty())  theFilePath     = weBookCommon->getFilelPath();
    if (theLogFolder.isEmpty()) theLogFolder    = weBookCommon->getLogFolderName();
    //
    //isLogToFile = true;
    //myLogPathFileName = QString("%1%2.log").arg(applicationName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    //qInstallMessageHandler(WeBookMessenger); // Install the Message handler
    //MyLogFile = QString("%1%2.log").arg(applicationName).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    weBookCommon->setAppName(theAppName);
    weBookCommon->setIniFileName(theInit);
    weBookCommon->setOrgName(theOrgName);
    weBookCommon->setOrgDomain(theOrgDomain);
    weBookCommon->setCryptoKey(theCryptoKey);
    weBookCommon->setCryptoIvVector(theCryptoIv);
    weBookCommon->setPort(thePort.toInt());
    weBookCommon->setLogPath(theLogPath);
    weBookCommon->setFilePath(theFilePath);
    weBookCommon->setLogFolderName(theLogFolder);
    weBookCommon->setWeBookLogger();
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
    weBookWindow->show();
    // QApplication::setStyle(QStyleFactory::create("fusion"));
    // QStyleFactory::keys= ("Windows", "Fusion")
    // QDEBUGTS << "QStyleFactory::keys=" << QStyleFactory::keys();
    return app.exec();
} // end main
/* ***************************** End of File ******************************* */
