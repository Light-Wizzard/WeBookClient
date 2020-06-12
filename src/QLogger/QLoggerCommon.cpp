/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerCommon.h"
namespace QLogger
{
    /******************************************************************************
    ** QLoggerCommon Constructor                                                  *
    *******************************************************************************/
    QLoggerCommon::QLoggerCommon(bool isLog)
    {
        //Q_UNUSED(isLog)
        if (isLog) setLogger();

    } // end QLoggerCommon
    /******************************************************************************
    ** QLoggerCommon Deconstructor                                                *
    *******************************************************************************/
    QLoggerCommon::~QLoggerCommon()
    {

    } // end ~QLoggerCommon
    /******************************************************************************
    ** setLogger                                                                  *
    *******************************************************************************/
    void QLoggerCommon::setLogger()
    {
        if (true)
        {
            const auto manager = QLoggerManager::getInstance();
            manager->addDestination(getLogFullPath(), getModuleName(), getLogLevel());
        }
    } // end setLogger
    /******************************************************************************
    ** qSettingsInstance                                                          *
    ** Creates QSettings for organizationName, organizationDomain, applicationName*
    **
    *******************************************************************************/
    void QLoggerCommon::qSettingsInstance()
    {
        // organizationName, organizationDomain, applicationName and applicationName
        // are set in main.cpp, and passed into Constuctor, so they are set
        QApplication::setOrganizationName(getOrgName());
        QApplication::setOrganizationDomain(getOrgDomain());
        QApplication::setApplicationName(getAppName());
        QApplication::setApplicationDisplayName(getAppName());
        // see *.pro file where it is: DEFINES *= APP_VERSION=$${VERSION}
        QApplication::setApplicationVersion(QObject::tr(APP_VERSION));
        QString myIni = getFullFilePathName(getIniFileName());

        if (!isFileMake(getFilelPath(), getIniFileName()))
        {
            qFatal("%s", QString("Error: cannot create file %1").arg(myIni).toLocal8Bit().constData());
        }
        // ${HOME}/AppName/data/AppName/AppName.ini
        mySettings  = new QSettings(myIni, QSettings::IniFormat);
    } // end qSettingsInstance
    /******************************************************************************
    ** combinePathFileName                                                        *
    *******************************************************************************/
    QString QLoggerCommon::combinePathFileName(QString thisPath, QString thisFileName)
    {
        return QString("%1%2%3").arg(thisPath, QDir::separator(), thisFileName);
    } // end combinePathFileName
    /******************************************************************************
    ** isFileExists                                                               *
    *******************************************************************************/
    bool QLoggerCommon::isFileExists(QString thisFile)
    {
        // check if file exists and if yes: Is it really a file and not directory?
        return QFileInfo::exists(thisFile) && QFileInfo(thisFile).isFile();
    } // end isFileExists
    /******************************************************************************
    ** isFileMake                                                                 *
    *******************************************************************************/
    bool QLoggerCommon::isFileMake(const QString &thisPath, const QString &thisFileName)
    {
        if (!isMakeDir(thisPath)) return false;
        if (!isFileExists(combinePathFileName(thisPath, thisFileName)))
        {
            QFile file(combinePathFileName(thisPath, thisFileName));
            if (file.open(QIODevice::WriteOnly))
            {
                file.close();
                return true;
            }
            else return false;
        }
        return true;
    } // end isFileMake
    /******************************************************************************
    ** isPathExists                                                               *
    *******************************************************************************/
    bool QLoggerCommon::isPathExists(QString thisPath)
    {
        return QDir(thisPath).exists();
    } // end isPathExists
    /******************************************************************************
    ** isPathMake                                                                 *
    *******************************************************************************/
    bool QLoggerCommon::isPathMake(const QString &thisRootPath, const QString &thisPath)
    {
        if (isMakeDir(thisRootPath))
        {
            if (isMakeDir(combinePathFileName(thisRootPath, thisPath)))
            {
                return true;
            }
        }
        return isFileExists(thisPath);
    } // end isPathMake
    /******************************************************************************
    ** isMakeDir                                                                  *
    *******************************************************************************/
    bool QLoggerCommon::isMakeDir(const QString &thisPath)
    {
        QDir dir(thisPath);
        if (!dir.exists())
        {
            if (!dir.mkpath("."))
            {
                qFatal("%s", QString("Error: cannot create file %1").arg(thisPath).toLocal8Bit().constData());
            }
            else return true;
        }
        return isPathExists(thisPath);
    } // end isMakeDir
    /******************************************************************************
    ** isSetting by key                                                           *
    *******************************************************************************/
    bool QLoggerCommon::isSetting(const QString &thisFieldName)
    {
        if (mySettings == nullptr)  qSettingsInstance();
        return mySettings->contains(thisFieldName);
    } // end isSetting
    /******************************************************************************
    ** getSetting by key and  default Value                                       *
    ** QString myName = getSetting("key", "default value");                       *
    *******************************************************************************/
    QVariant QLoggerCommon::getSetting(const QString &key, const QVariant &defaultValue)
    {
        if (mySettings == nullptr) qSettingsInstance();
        if (!isSetting(key))
        {
            setSetting(key, defaultValue);
            return defaultValue;
        }
        qDebug() << "QLoggerCommon::getSettings=" << mySettings->value(key, defaultValue);
        return mySettings->value(key, defaultValue);
    } // end getSetting
    /******************************************************************************
    ** setSetting using key and settingValue                                      *
    ** setSetting("this_key", "to this");                                         *
    ** QVariant is used for value, so it can be anything it supports              *
    *******************************************************************************/
    void QLoggerCommon::setSetting(const QString &thisKey, const QVariant &defaultValue)
    {
        if (mySettings == nullptr) qSettingsInstance();
        mySettings->setValue(thisKey, defaultValue);
    } // end setSetting
    /******************************************************************************
    ** getOrgName                                                                 *
    ** This value is used for Qt Settings: GitHub Account Name is one example     *
    *******************************************************************************/
    QString QLoggerCommon::getOrgName()
    {
        if (myOrganizationName.isEmpty()) myOrganizationName = constOrgName;
        return myOrganizationName;
    } // end getOrgName
    /******************************************************************************
    ** setOrgName(myValue)                                                        *
    *******************************************************************************/
    void QLoggerCommon::setOrgName(const QString &thisOrgName)
    {
        if (myOrganizationName != thisOrgName)
        {
            myOrganizationName = thisOrgName;
            emit handelSettinChanged();
        }
    } // end setOrgName
    /******************************************************************************
    ** getOrgDomain                                                               *
    *******************************************************************************/
    QString QLoggerCommon::getOrgDomain()
    {
        if (myOrganizationDomain.isEmpty()) myOrganizationDomain = constOrgDomain;
        return myOrganizationDomain;
    } // end getOrgDomain
    /******************************************************************************
    ** setOrgDomain(myValue)                                                      *
    *******************************************************************************/
    void QLoggerCommon::setOrgDomain(const QString &thisOrgDomain)
    {
        if (myOrganizationDomain != thisOrgDomain)
        {
            myOrganizationDomain = thisOrgDomain;
            emit handelSettinChanged();
        }
    } // end setOrgDomain
    /******************************************************************************
    ** getAppName                                                                 *
    *******************************************************************************/
    QString QLoggerCommon::getAppName()
    {
        if (myApplicationName.isEmpty()) myApplicationName = constAppName;
        return myApplicationName;
    } // end getAppName
    /******************************************************************************
    ** setAppName(myValue)                                                        *
    *******************************************************************************/
    void QLoggerCommon::setAppName(const QString &thisAppName)
    {
        if (myApplicationName != thisAppName)
        {
            myApplicationName = thisAppName;
            emit handelSettinChanged();
        }
    } // end setAppName
    /******************************************************************************
    ** getIniFileName                                                             *
    ** File Name only                                                             *
    *******************************************************************************/
    QString QLoggerCommon::getIniFileName()
    {
        if (myIniFileName.isEmpty()) myIniFileName = constIniFileName;
        return myIniFileName;
    } // end getIniFileName
    /******************************************************************************
    ** setIniFileName                                                             *
    *******************************************************************************/
    void QLoggerCommon::setIniFileName(const QString &thisIniFileName)
    {
        if (myIniFileName != thisIniFileName)
        {
            myIniFileName = thisIniFileName;
            emit handelSettinChanged();
        }
    } // end setIniFileName
    /******************************************************************************
    ** getLogPath                                                                 *
    ** FIXME argument error
    *******************************************************************************/
    QString QLoggerCommon::getLogPath()
    {
        myLogPath = QString("%1%2%3").arg(getHomePath(), QDir::separator(), getAppName());
        myLogPath = QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getLogFolderName());

        if (myLogPath.isEmpty()) myLogPath = QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getLogFolderName());

        if (!isMakeDir(QString("%1%2%3").arg(getHomePath(), QDir::separator(), getAppName())))
        {
            qFatal("%s", QString("Error: cannot create Folder %1").arg(QString("%1%2%3").arg(getHomePath(), QDir::separator(), getAppName())).toLocal8Bit().constData());
        }
        if (!isMakeDir(QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getLogFolderName())))
        {
            qFatal("%s", QString("Error: cannot create Folder %1").arg(QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getLogFolderName())).toLocal8Bit().constData());
        }
        return myLogPath;
    } // end getLogPath
    /******************************************************************************
    ** setLogPath                                                                 *
    *******************************************************************************/
    void QLoggerCommon::setLogPath(const QString &thisLogPath)
    {
        if (myLogPath != thisLogPath)
        {
            myLogPath = thisLogPath;
            emit handelSettinChanged();
        }
    } // end setDataFullPath
    /******************************************************************************
    ** getLogFolderName                                                           *
    *******************************************************************************/
    QString QLoggerCommon::getLogFolderName()
    {
        if (myLogFolderName.isEmpty()) myLogFolderName = constLogFolderName;
        return myLogFolderName;
    } // end getLogFolderName
    /******************************************************************************
    ** setLogFolderName                                                           *
    *******************************************************************************/
    void QLoggerCommon::setLogFolderName(const QString &thisLogFolderName)
    {
        if (myLogFolderName != thisLogFolderName)
        {
            myLogFolderName = thisLogFolderName;
            emit handelSettinChanged();
        }
    } // end setLogFolderName
    /******************************************************************************
    ** getLogFileName                                                             *
    ** The Auto setting uses AppName + Pattern + Extension                        *
    *******************************************************************************/
    QString QLoggerCommon::getLogFileName()
    {
        if (myLogFileName.isEmpty()) myLogFileName = QString("%1%2.%3").arg(getAppName(), QDateTime::currentDateTime().toString(getLogNamePattern()), getLogFileExtension());
        return myLogFileName;
    } // end getLogFileName
    /******************************************************************************
    ** setLogFileName                                                             *
    *******************************************************************************/
    void QLoggerCommon::setLogFileName(const QString &thisLogFileName)
    {
        if (myLogFileName != thisLogFileName)
        {
            myLogFileName = thisLogFileName;
            emit handelSettinChanged();
        }
    } // end setLogFileName
    /******************************************************************************
    ** getLogNamePattern                                                          *
    *******************************************************************************/
    QString QLoggerCommon::getLogNamePattern()
    {
        if (myLogNamePattern.isEmpty()) myLogNamePattern = constLogNamePattern;
        return myLogNamePattern;
    } // end getLogNamePattern
    /******************************************************************************
    ** setLogNamePattern                                                          *
    *******************************************************************************/
    void QLoggerCommon::setLogNamePattern(const QString &thisLogNamePattern)
    {
        if (myLogNamePattern != thisLogNamePattern)
        {
            myLogNamePattern = thisLogNamePattern;
            emit handelSettinChanged();
        }
    } // end setLogNamePattern
    /******************************************************************************
    ** getFileFolderName                                                          *
    *******************************************************************************/
    QString QLoggerCommon::getFileFolderName()
    {
        if (myFileFolderName.isEmpty()) myFileFolderName = constFileFolderName;
        return myFileFolderName;
    } // end getFileFolderName
    /******************************************************************************
    ** setFileFolderName                                                          *
    *******************************************************************************/
    void QLoggerCommon::setFileFolderName(const QString &thisFileFolderName)
    {
        if (myFileFolderName != thisFileFolderName)
        {
            myFileFolderName = thisFileFolderName;
            emit handelSettinChanged();
        }
    } // end setFileFolderName
    /******************************************************************************
    ** getLogFileExtension                                                        *
    *******************************************************************************/
    QString QLoggerCommon::getLogFileExtension()
    {
        if (myLogFileExtension.isEmpty()) myLogFileExtension = constLogFileExtension;
        return myLogFileExtension;
    } // end getLogFileExtension
    /******************************************************************************
    ** setLogFileExtension                                                        *
    *******************************************************************************/
    void QLoggerCommon::setLogFileExtension(const QString &thisLogFileExtension)
    {
        if (myLogFileExtension != thisLogFileExtension)
        {
            myLogFileExtension = thisLogFileExtension;
            emit handelSettinChanged();
        }
    } // end setLogFileExtension
    /******************************************************************************
    ** getLogFullPath                                                             *
    ** ${HOME}/AppName/LogFolderName/LogFileName.LogFileExtension
    *******************************************************************************/
    QString QLoggerCommon::getLogFullPath()
    {
        if (myLogFullPath.isEmpty()) myLogFullPath = QString("%1%2%3%4%5%6%7").arg(getLogPath(), QDir::separator(), getAppName(), QDir::separator(), getLogFolderName(), QDir::separator(), getLogFileName());
        return myLogFullPath;
    } // end getLogFullPath
    /******************************************************************************
    ** setLogFullPath                                                             *
    *******************************************************************************/
    void QLoggerCommon::setLogFullPath(const QString &thisLogFullPath)
    {
        if (myLogFullPath != thisLogFullPath)
        {
            myLogFullPath = thisLogFullPath;
            emit handelSettinChanged();
        }
    } // end setLogFullPath
    /******************************************************************************
    ** getModuleName                                                              *
    *******************************************************************************/
    QString QLoggerCommon::getModuleName()
    {
        if (myModuleName.isEmpty()) myModuleName = constModuleName;
        return myModuleName;
    } // end getModuleName
    /******************************************************************************
    ** setModuleName                                                              *
    *******************************************************************************/
    void QLoggerCommon::setModuleName(const QString &thisModuleName)
    {
        if (myModuleName != thisModuleName)
        {
            myModuleName = thisModuleName;
            emit handelSettinChanged();
        }
    } // end setModuleName
    /******************************************************************************
    ** getLogLevel                                                                *
    *******************************************************************************/
    QLoggerLevel::LogLevel QLoggerCommon::getLogLevel()
    {
        return myLogLevel;
    } // end getLogLevel
    /******************************************************************************
    ** setLogLevel                                                                *
    *******************************************************************************/
    void QLoggerCommon::setLogLevel(QLoggerLevel::LogLevel thisLogLevel)
    {
        if (myLogLevel != thisLogLevel)
        {
            myLogLevel = thisLogLevel;
            emit handelSettinChanged();
        }
    } // end setLogLevel
    /******************************************************************************
    ** getFilelPath                                                               *
    ** /constDataFolderName/
    *******************************************************************************/
    QString QLoggerCommon::getFilelPath()
    {
        if (myFilePath.isEmpty()) myFilePath = QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getFileFolderName());
        return myFilePath;
    } // end getFilelPath
    /******************************************************************************
    ** setFilePath                                                                *
    *******************************************************************************/
    void QLoggerCommon::setFilePath(const QString &thisDataFullPath)
    {
        if (myFilePath != thisDataFullPath)
        {
            myFilePath = thisDataFullPath;
            emit handelSettinChanged();
        }
    } // end setFilePath
    /******************************************************************************
    ** getHomePath                                                                *
    *******************************************************************************/
    QString QLoggerCommon::getHomePath()
    {
        if (myHomePath.isEmpty()) myHomePath = constHomeLocation;
        return myHomePath;
    } // end getHomePath
    /******************************************************************************
    ** setHomePath                                                                *
    *******************************************************************************/
    void QLoggerCommon::setHomePath(const QString &thisHomePath)
    {
        if (myHomePath != thisHomePath)
        {
            myHomePath = thisHomePath;
            emit handelSettinChanged();
        }
    } // end setHomePath
    /******************************************************************************
    ** getUserName                                                                *
    *******************************************************************************/
    QString QLoggerCommon::getUserName()
    {
        if (myUserName.isEmpty()) setUserName("");
        return myUserName;
    } // end getUserName
    /******************************************************************************
    ** setUserName                                                                *
    *******************************************************************************/
    void QLoggerCommon::setUserName(const QString &thisUserName)
    {
        if (myUserName.isEmpty() || thisUserName.isEmpty())
        {
            myUserName = qgetenv("USER");
            if (myUserName.isEmpty()) myUserName = qgetenv("USERNAME");
            if (myUserName.isEmpty())
            {
                // FIXME Add OS Specific ways to get User Name if above fails
                #if   defined(Q_OS_ANDROID)
                #elif defined(Q_OS_BLACKBERRY)
                #elif defined(Q_OS_IOS)
                #elif defined(Q_OS_MAC)
                #elif defined(Q_OS_WINCE)
                #elif defined(Q_OS_WIN)
                // FIXME add header for MAX_USERNAME DWORD
                //  char acUserName[MAX_USERNAME];
                //  DWORD nUserName = sizeof(acUserName);
                //  if (GetUserName(acUserName, &nUserName)) myUserName = acUserName;
                #elif defined(Q_OS_LINUX)
                #elif defined(Q_OS_UNIX)
                #else
                #endif
            }
            if (!myUserName.isEmpty()) emit handelSettinChanged();
            else qWarning() << "Failed to find User Name";
        }
        //
        if (myUserName != thisUserName)
        {
            myUserName = thisUserName;
            emit handelSettinChanged();
        }
    } // end setUserName
    /******************************************************************************
    ** portToString                                                               *
    ** Valid Port Numbers range varies on plateform                               *
    ** Typical Ports: 8080                                                        *
    *******************************************************************************/
    QString QLoggerCommon::portToString()
    {
        if (myPort == 0) myPort = ConstPort;
        return QString::number(myPort);
    } // end portToString
    /******************************************************************************
    ** getPort                                                                    *
    ** Valid Port Numbers range varies on plateform                               *
    ** Typical Ports: 8080                                                        *
    *******************************************************************************/
    quint16 QLoggerCommon::getPort()
    {
        if (myPort == 0) myPort = ConstPort;
        return myPort;
    } // end getPort
    /******************************************************************************
    ** setPort(int thisPort)                                                      *
    *******************************************************************************/
    void QLoggerCommon::setPort(quint16 thisPort)
    {
        if (myPort != 0 && myPort != thisPort)
        {
            // Update
            myPort = thisPort;
        }
        else
        {
            // Set first time
            myPort = thisPort;
        }
    } // end setPort
    /******************************************************************************
    ** setFilePath(QString myFileName)                                            *
    ** All files must be in folder constAppFolder                                 *
    ** This folder is different for debug vs release as well as deployed          *
    *******************************************************************************/
    QString QLoggerCommon::setFilePath(QString thisFileName, QString thisDataFolderName)
    {
        // Make sure Build Folder does not contain the App Name, this is default, change Projects Build Path
        if (constAppDataLocation.contains(constAppFolder))
        {
            if (QDir(constAppDataLocation).exists())
            {
                // I have no idea where this is at till I deploy it
            }
        }
        // If running from within Qt Creator, this path is outside of the root application folder
        QDir dataFileDir(QCoreApplication::applicationDirPath());
        // full_path/databaseFolderName/databaseFileName
        QString dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("%1%2%3").arg(thisDataFolderName, QDir::separator(), thisFileName)));
        // If ran from within Qt Creator
        if (!dataFullPath.contains(constAppFolder))
        {
            // APP_FOLDER/databaseFolderName/databaseFileName
            dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1%2%3%4%5%6").arg(QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
            qDebug() << QString("..%1%2%3%4%5%6").arg(QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
        }
        if (!QFile(dataFullPath).exists())
        {
            dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2%3%4%5%6%7").arg(QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
            qDebug() << QString("..%1..%2%3%4%5%6%7").arg(QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
        }
        if (!QFile(dataFullPath).exists())
        {
            dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator(), QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
            qDebug() << QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator(), QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
        }
        if (!QFile(dataFullPath).exists())
        {
            qDebug() << "setFilePath cannot find folder";
        }
        return dataFullPath;
    } // end setFilePath
    /******************************************************************************
    ** getFullFilePathName                                                        *
    *******************************************************************************/
    QString QLoggerCommon::getFullFilePathName(QString thisFileName)
    {
        return QString("%1%2%3").arg(getFilelPath(), QDir::separator(), thisFileName);
    } // end getFullFilePathName
    /******************************************************************************
    ** setGeometry                                                                *
    *******************************************************************************/
    void QLoggerCommon::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
    {
        setSetting(ConstSettingsGeometryPos, thisPos);
        if(!isMax && !isMin) setSetting(ConstSettingsGeometrySize, thisSize);
        setSetting(ConstSettingsGeometryMax, isMax);
        setSetting(ConstSettingsGeometryMin, isMin);
    } // end setGeometry
    /******************************************************************************
    ** getGeometryPos                                                             *
    *******************************************************************************/
    QPoint QLoggerCommon::getGeometryPos(const QPoint &thisDefaultValue)
    {
        return getSetting(ConstSettingsGeometryPos, thisDefaultValue).toPoint();
    } // end getGeometryPos
    /******************************************************************************
    ** getGeometrySize                                                            *
    *******************************************************************************/
    QSize QLoggerCommon::getGeometrySize(const QSize &thisDefaultValue)
    {
        return getSetting(ConstSettingsGeometrySize, thisDefaultValue).toSize();
    } // end getGeometrySize
    /******************************************************************************
    ** getGeometryMax                                                             *
    *******************************************************************************/
    bool QLoggerCommon::getGeometryMax(const bool &thisDefaultValue)
    {
        return getSetting(ConstSettingsGeometryMax, thisDefaultValue).toBool();
    } // end getGeometryMax
    /******************************************************************************
    ** getGeometryMin                                                             *
    *******************************************************************************/
    bool QLoggerCommon::getGeometryMin(const bool &thisDefaultValue)
    {
        return getSetting(ConstSettingsGeometryMin, thisDefaultValue).toBool();
    } // end getGeometryMin
} // end namespace QLogger
/* ***************************** End of File ******************************* */
