/**************************************************************************
* WeBookSettings                                                          *
***************************************************************************/
#include "WeBookSettings.h"
/**************************************************************************
* WeBookSettings Constructor                                              *
* \fn WeBookSettings::WeBookSettings(QObject *parent) : QObject(parent)
***************************************************************************/
WeBookSettings::WeBookSettings(QObject *parent) : QObject(parent)
{
    // Connect after you set the Logger as to not generate events
    connect(this, &WeBookSettings::handelSettinChanged, this, &WeBookSettings::onSettinChanged);
} // end WeBookSettings
/**************************************************************************
* WeBookSettings Deconstructor                                            *
* \fn WeBookSettings::~WeBookSettings()
***************************************************************************/
WeBookSettings::~WeBookSettings()
{

} // end ~WeBookSettings
/**************************************************************************
* \fn void WeBookSettings::onSettinChanged()
***************************************************************************/
void WeBookSettings::onSettinChanged()
{
    qSettingsInstance();
} // end onSettinChanged
/**************************************************************************
* \fn QString WeBookSettings::getHomePath()
***************************************************************************/
QString WeBookSettings::getHomePath()
{
    if (myHomePath.isEmpty()) myHomePath = ConstDefaultHomeLocation;
    return myHomePath;
} // end getHomePath
/**************************************************************************
* \fn void WeBookSettings::setHomePath(const QString &thisHomePath)
***************************************************************************/
void WeBookSettings::setHomePath(const QString &thisHomePath)
{
    if (myHomePath != thisHomePath)
    {
        myHomePath = thisHomePath;
        emit handelSettinChanged();
    }
} // end setHomePath
/**************************************************************************
* \fn QString WeBookSettings::getUserName()
***************************************************************************/
QString WeBookSettings::getUserName()
{
    if (myUserName.isEmpty()) setUserName("");
    return myUserName;
} // end getUserName
/**************************************************************************
* \fn void WeBookSettings::setUserName(const QString &thisUserName)
***************************************************************************/
void WeBookSettings::setUserName(const QString &thisUserName)
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
            // #include "winbase.h"
            // #include "windows. h"
            //  char acUserName[MAX_USERNAME];
            //  DWORD nUserName = sizeof(acUserName);
            //  if (GetUserName(acUserName, &nUserName)) myUserName = acUserName;
#elif defined(Q_OS_LINUX)
#elif defined(Q_OS_UNIX) && !defined(Q_OS_LINUX)
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
* \fn QString WeBookSettings::getPassword()
*******************************************************************************/
QString WeBookSettings::getPassword()
{
    return myPassword;
} // end getPassword
/******************************************************************************
* \fn void WeBookSettings::setPassword(const QString &thisPassword)
*******************************************************************************/
void WeBookSettings::setPassword(const QString &thisPassword)
{
    if (myPassword.isEmpty() || myPassword != thisPassword)
    {
        myPassword = thisPassword;
    }
} // end setPassword
/******************************************************************************
* \fn QString WeBookSettings::getUrl()
*
*******************************************************************************/
QString WeBookSettings::getUrl()
{
    if (myUrl.isEmpty()) myUrl = ConstDefaultUrl;
    return myUrl;
} // end getUrl
/******************************************************************************
* \fn void WeBookSettings::setUrl(const QString &thisUrl)
*
*******************************************************************************/
void WeBookSettings::setUrl(const QString &thisUrl)
{
    if (myUrl.isEmpty() || myUrl != thisUrl)
    {
        myUrl = thisUrl;
    }
} // end setUrl
/**************************************************************************
* \fn void WeBookSettings::qSettingsInstance()
* Creates QSettings for organizationName, organizationDomain, applicationName*
***************************************************************************/
void WeBookSettings::qSettingsInstance()
{
    // organizationName, organizationDomain, applicationName and applicationName
    // are set in main.cpp, and passed into Constuctor, so they are set
    QCoreApplication::setOrganizationName(getOrgName());
    QCoreApplication::setOrganizationDomain(getOrgDomain());
    QCoreApplication::setApplicationName(getAppName());
    //QCoreApplication::setApplicationDisplayName(getAppName());
    // see *.pro file where it is: DEFINES *= APP_VERSION=$${VERSION}
    QCoreApplication::setApplicationVersion(QObject::tr(APP_VERSION));
    QString myIni = getFullFilePathName(getIniFileName());

    if (!isFileMake(getFilelPath(), getIniFileName()))
    {
        qFatal("%s", QString("Error: cannot create file %1").arg(myIni).toLocal8Bit().constData());
    }
    // ${HOME}/AppName/data/AppName/AppName.ini
    mySettings  = new QSettings(myIni, QSettings::IniFormat);
    isSet = true;
} // end qSettingsInstance
/**************************************************************************
* \fn QString WeBookSettings::combinePathFileName(QString thisPath, QString thisFileName)
***************************************************************************/
QString WeBookSettings::combinePathFileName(QString thisPath, QString thisFileName)
{
    return QString("%1%2%3").arg(thisPath, QDir::separator(), thisFileName);
} // end combinePathFileName
/**************************************************************************
* \fn bool WeBookSettings::isFileExists(QString thisFile)
***************************************************************************/
bool WeBookSettings::isFileExists(QString thisFile)
{
    // check if file exists and if yes: Is it really a file and not directory?
    return QFileInfo::exists(thisFile) && QFileInfo(thisFile).isFile();
} // end isFileExists
/**************************************************************************
* \fn bool WeBookSettings::isFileMake(const QString &thisPath, const QString &thisFileName)
***************************************************************************/
bool WeBookSettings::isFileMake(const QString &thisPath, const QString &thisFileName)
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
/**************************************************************************
* \fn bool WeBookSettings::isPathExists(QString thisPath)
***************************************************************************/
bool WeBookSettings::isPathExists(QString thisPath)
{
    return QDir(thisPath).exists();
} // end isPathExists
/**************************************************************************
* \fn bool WeBookSettings::isPathMake(const QString &thisRootPath, const QString &thisPath)
***************************************************************************/
bool WeBookSettings::isPathMake(const QString &thisRootPath, const QString &thisPath)
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
/**************************************************************************
* \fn bool WeBookSettings::isMakeDir(const QString &thisPath)
***************************************************************************/
bool WeBookSettings::isMakeDir(const QString &thisPath)
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
/**************************************************************************
* \fn QString WeBookSettings::joinFilePath(QString thisFileName, QString thisDataFolderName)
* All files must be in folder constAppFolder                             *
* This folder is different for debug vs release as well as deployed      *
***************************************************************************/
QString WeBookSettings::findJoinFilePath(QString thisFileName, QString thisDataFolderName)
{
    // Make sure Build Folder does not contain the App Name, this is default, change Projects Build Path
    if (ConstDefaultAppDataLocation.contains(ConstDefaultAppFolder))
    {
        if (QDir(ConstDefaultAppDataLocation).exists())
        {
            // I have no idea where this is at till I deploy it
        }
    }
    // If running from within Qt Creator, this path is outside of the root application folder
    QDir dataFileDir(QCoreApplication::applicationDirPath());
    // full_path/databaseFolderName/databaseFileName
    QString dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("%1%2%3").arg(thisDataFolderName, QDir::separator(), thisFileName)));
    // If ran from within Qt Creator
    if (!dataFullPath.contains(ConstDefaultAppFolder))
    {
        // APP_FOLDER/databaseFolderName/databaseFileName
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1%2%3%4%5%6").arg(QDir::separator(), ConstDefaultAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
        //qDebug() << QString("..%1%2%3%4%5%6").arg(QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
    }
    if (!QFile(dataFullPath).exists())
    {
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2%3%4%5%6%7").arg(QDir::separator(), QDir::separator(), ConstDefaultAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
        //qDebug() << QString("..%1..%2%3%4%5%6%7").arg(QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
    }
    if (!QFile(dataFullPath).exists())
    {
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator(), QDir::separator(), QDir::separator(), ConstDefaultAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName)));
        //qDebug() << QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator(), QDir::separator(), QDir::separator(), constAppFolder, QDir::separator(), thisDataFolderName, QDir::separator(), thisFileName);
    }
    if (!QFile(dataFullPath).exists())
    {
        //qDebug() << "setFilePath cannot find folder";
    }
    return dataFullPath;
} // end setFilePath
/**************************************************************************
* \fn QString WeBookSettings::getFullFilePathName(QString thisFileName)
***************************************************************************/
QString WeBookSettings::getFullFilePathName(QString thisFileName)
{
    return QString("%1%2%3").arg(getFilelPath(), QDir::separator(), thisFileName);
} // end getFullFilePathName
/**************************************************************************
* \fn QString WeBookSettings::getFilelPath()
***************************************************************************/
QString WeBookSettings::getFilelPath()
{
    if (myFilePath.isEmpty()) myFilePath = QString("%1%2%3%4%5").arg(getHomePath(), QDir::separator(), getAppName(), QDir::separator(), getFileFolderName());
    return myFilePath;
} // end getFilelPath
/**************************************************************************
* \fn void WeBookSettings::setFilePath(const QString &thisDataFullPath)
***************************************************************************/
void WeBookSettings::setFilePath(const QString &thisDataFullPath)
{
    if (myFilePath != thisDataFullPath)
    {
        myFilePath = thisDataFullPath;
        emit handelSettinChanged();
    }
} // end setFilePath
/**************************************************************************
* FIXME argument error
* \fn QString WeBookSettings::getLogPath()
***************************************************************************/
QString WeBookSettings::getLogPath()
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
/**************************************************************************
* \fn void WeBookSettings::setLogPath(const QString &thisLogPath)
***************************************************************************/
void WeBookSettings::setLogPath(const QString &thisLogPath)
{
    if (myLogPath != thisLogPath)
    {
        myLogPath = thisLogPath;
        emit handelSettinChanged();
    }
} // end setDataFullPath
/**************************************************************************
* \fn QString WeBookSettings::getLogFolderName()
***************************************************************************/
QString WeBookSettings::getLogFolderName()
{
    if (myLogFolderName.isEmpty())
    {
        if (isSet)
            myLogFolderName = getSetting(ConstSettingsLogFolder, ConstDefaultLogFolderName).toString();
        else
            myLogFolderName = ConstDefaultLogFolderName;
    }
    return myLogFolderName;
} // end getLogFolderName
/**************************************************************************
* \fn void WeBookSettings::setLogFolderName(const QString &thisLogFolderName)
***************************************************************************/
void WeBookSettings::setLogFolderName(const QString &thisLogFolderName)
{
    if (myLogFolderName != thisLogFolderName)
    {
        myLogFolderName = thisLogFolderName;
        emit handelSettinChanged();
    }
} // end setLogFolderName
/**************************************************************************
* \fn QString WeBookSettings::getLogFileName()
* The Auto setting uses AppName + Pattern + Extension                    *
***************************************************************************/
QString WeBookSettings::getLogFileName()
{
    if (myLogFileName.isEmpty()) myLogFileName = QString("%1%2.%3").arg(getAppName(), QDateTime::currentDateTime().toString(getLogNamePattern()), getLogFileExtension());
    return myLogFileName;
} // end getLogFileName
/**************************************************************************
* \fn void WeBookSettings::setLogFileName(const QString &thisLogFileName)
***************************************************************************/
void WeBookSettings::setLogFileName(const QString &thisLogFileName)
{
    if (myLogFileName != thisLogFileName)
    {
        myLogFileName = thisLogFileName;
        emit handelSettinChanged();
    }
} // end setLogFileName
/**************************************************************************
* \fn QString WeBookSettings::getLogNamePattern()
***************************************************************************/
QString WeBookSettings::getLogNamePattern()
{
    if (myLogNamePattern.isEmpty())
    {
        if (isSet)
            myLogNamePattern = getSetting(ConstSettingsLogNamePattern, ConstDefaultLogNamePattern).toString();
        else
            myLogNamePattern = ConstDefaultLogNamePattern;
    }
    return myLogNamePattern;
} // end getLogNamePattern
/**************************************************************************
* \fn void WeBookSettings::setLogNamePattern(const QString &thisLogNamePattern)
***************************************************************************/
void WeBookSettings::setLogNamePattern(const QString &thisLogNamePattern)
{
    if (myLogNamePattern != thisLogNamePattern)
    {
        myLogNamePattern = thisLogNamePattern;
        emit handelSettinChanged();
    }
} // end setLogNamePattern
/**************************************************************************
* \fn QString WeBookSettings::getFileFolderName()
***************************************************************************/
QString WeBookSettings::getFileFolderName()
{
    if (myFileFolderName.isEmpty())
    {
        if (isSet)
            myFileFolderName = getSetting(ConstSettingsFileFolder, ConstDefaultFileFolderName).toString();
        else
            myFileFolderName = ConstDefaultFileFolderName;
    }
    return myFileFolderName;
} // end getFileFolderName
/**************************************************************************
* \fn void WeBookSettings::setFileFolderName(const QString &thisFileFolderName)
***************************************************************************/
void WeBookSettings::setFileFolderName(const QString &thisFileFolderName)
{
    if (myFileFolderName != thisFileFolderName)
    {
        myFileFolderName = thisFileFolderName;
        emit handelSettinChanged();
    }
} // end setFileFolderName
/**************************************************************************
* \fn QString WeBookSettings::getLogFileExtension()
***************************************************************************/
QString WeBookSettings::getLogFileExtension()
{
    if (myLogFileExtension.isEmpty())
    {
        if (isSet)
            myLogFileExtension = getSetting(ConstSettingsLogFileExt, ConstDefaultLogFileExtension).toString();
        else
            myLogFileExtension = ConstDefaultLogFileExtension;
    }
    return myLogFileExtension;
} // end getLogFileExtension
/**************************************************************************
* \fn void WeBookSettings::setLogFileExtension(const QString &thisLogFileExtension)
***************************************************************************/
void WeBookSettings::setLogFileExtension(const QString &thisLogFileExtension)
{
    if (myLogFileExtension != thisLogFileExtension)
    {
        myLogFileExtension = thisLogFileExtension;
        emit handelSettinChanged();
    }
} // end setLogFileExtension
/**************************************************************************
* \fn QString WeBookSettings::getLogFullPath()
* ${HOME}/AppName/LogFolderName/LogFileName.LogFileExtension
***************************************************************************/
QString WeBookSettings::getLogFullPath()
{
    if (myLogFullPath.isEmpty()) myLogFullPath = QString("%1%2%3").arg(getLogPath(), QDir::separator(), getLogFileName());
    return myLogFullPath;
} // end getLogFullPath
/**************************************************************************
* \fn void WeBookSettings::setLogFullPath(const QString &thisLogFullPath)
***************************************************************************/
void WeBookSettings::setLogFullPath(const QString &thisLogFullPath)
{
    if (myLogFullPath != thisLogFullPath)
    {
        myLogFullPath = thisLogFullPath;
        emit handelSettinChanged();
    }
} // end setLogFullPath
/**************************************************************************
* \fn bool WeBookSettings::isSetting(const QString &thisFieldName)
***************************************************************************/
bool WeBookSettings::isSetting(const QString &thisFieldName)
{
    if (mySettings == nullptr)  qSettingsInstance();
    return mySettings->contains(thisFieldName);
} // end isSetting
/**************************************************************************
* \fn QVariant WeBookSettings::getSetting(const QString &key, const QVariant &defaultValue)
* QString myName = getSetting("key", "default value");                   *
***************************************************************************/
QVariant WeBookSettings::getSetting(const QString &key, const QVariant &defaultValue)
{
    if (mySettings == nullptr) qSettingsInstance();
    if (!isSetting(key))
    {
        setSetting(key, defaultValue);
        return defaultValue;
    }
    //qDebug() << "WeBookSettings::getSettings=" << mySettings->value(key, defaultValue);
    return mySettings->value(key, defaultValue);
} // end getSetting
/**************************************************************************
* setSetting using key and settingValue                                  *
* setSetting("this_key", "to this");                                     *
* QVariant is used for value, so it can be anything it supports          *
* \fn void WeBookSettings::setSetting(const QString &thisKey, const QVariant &defaultValue)
***************************************************************************/
void WeBookSettings::setSetting(const QString &thisKey, const QVariant &defaultValue)
{
    if (mySettings == nullptr) qSettingsInstance();
    mySettings->setValue(thisKey, defaultValue);
} // end setSetting
/**************************************************************************
* \fn QString WeBookSettings::getOrgName()
* This value is used for Qt Settings: GitHub Account Name is one example *
***************************************************************************/
QString WeBookSettings::getOrgName()
{
    if (myOrganizationName.isEmpty())
    {
        if (isSet)
            myOrganizationName = getSetting(ConstSettingsOrgName, ConstDefaultOrgName).toString();
        else
            myOrganizationName = ConstDefaultOrgName;
    }
    return myOrganizationName;
} // end getOrgName
/**************************************************************************
* \fn void WeBookSettings::setOrgName(const QString &thisOrgName)
***************************************************************************/
void WeBookSettings::setOrgName(const QString &thisOrgName)
{
    if (myOrganizationName != thisOrgName)
    {
        myOrganizationName = thisOrgName;
        emit handelSettinChanged();
    }
} // end setOrgName
/**************************************************************************
* \fn QString WeBookSettings::getOrgDomain()
***************************************************************************/
QString WeBookSettings::getOrgDomain()
{
    if (myOrganizationDomain.isEmpty())
    {
        if (isSet)
            myOrganizationDomain = getSetting(ConstSettingsOrgDomain, ConstDefaultOrgDomain).toString();
        else
            myOrganizationDomain = ConstDefaultOrgName;
    }
    return myOrganizationDomain;
} // end getOrgDomain
/**************************************************************************
* \fn void WeBookSettings::setOrgDomain(const QString &thisOrgDomain)
***************************************************************************/
void WeBookSettings::setOrgDomain(const QString &thisOrgDomain)
{
    if (myOrganizationDomain != thisOrgDomain)
    {
        myOrganizationDomain = thisOrgDomain;
        emit handelSettinChanged();
    }
} // end setOrgDomain
/**************************************************************************
* \fn QString WeBookSettings::getAppName()
***************************************************************************/
QString WeBookSettings::getAppName()
{
    if (myApplicationName.isEmpty())
    {
        if (isSet)
            myApplicationName = getSetting(ConstSettingsApplicationName, ConstDefaultAppName).toString();
        else
            myApplicationName = ConstDefaultAppName;
    }
    return myApplicationName;
} // end getAppName
/**************************************************************************
* \fn void WeBookSettings::setAppName(const QString &thisAppName)
***************************************************************************/
void WeBookSettings::setAppName(const QString &thisAppName)
{
    if (myApplicationName != thisAppName)
    {
        myApplicationName = thisAppName;
        emit handelSettinChanged();
    }
} // end setAppName
/**************************************************************************
* \fnQString WeBookSettings::getIniFileName()
* File Name only                                                         *
***************************************************************************/
QString WeBookSettings::getIniFileName()
{
    if (myIniFileName.isEmpty())
    {
        if (isSet)
            myIniFileName = getSetting(ConstSettingsIniFileName, ConstDefaultIniFileName).toString();
        else
            myIniFileName = ConstDefaultIniFileName;
    }
    return myIniFileName;
} // end getIniFileName
/**************************************************************************
* \fn void WeBookSettings::setIniFileName(const QString &thisIniFileName)
***************************************************************************/
void WeBookSettings::setIniFileName(const QString &thisIniFileName)
{
    if (myIniFileName != thisIniFileName)
    {
        myIniFileName = thisIniFileName;
        setSetting(ConstSettingsIniFileName, myIniFileName);
        emit handelSettinChanged();
    }
} // end setIniFileName
/**************************************************************************
* Valid Port Numbers range varies on plateform                            *
* Typical Ports: 8080                                                     *
* \fn QString WeBookSettings::portToString()
***************************************************************************/
QString WeBookSettings::portToString()
{
    if (myPort == 0) myPort = getPort();
    return QString::number(myPort);
} // end portToString
/**************************************************************************
* \fn quint16 WeBookSettings::getPort()
* Valid Port Numbers range varies on plateform                           *
* Typical Ports: 8080                                                    *
***************************************************************************/
quint16 WeBookSettings::getPort()
{
    if (myPort == 0)
    {
        if (isSet)
            myPort = getSetting(ConstSettingsPort, ConstDefaultPort).toInt();
        else
            myPort = ConstDefaultPort;
    }
    return myPort;
} // end getPort
/**************************************************************************
* \fn void WeBookSettings::setPort(quint16 thisPort)
***************************************************************************/
void WeBookSettings::setPort(quint16 thisPort)
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
/**************************************************************************
* \fn void WeBookSettings::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
***************************************************************************/
void WeBookSettings::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
{
    setSetting(ConstSettingsGeometryPos, thisPos);
    if(!isMax && !isMin) setSetting(ConstSettingsGeometrySize, thisSize);
    setSetting(ConstSettingsGeometryMax, isMax);
    setSetting(ConstSettingsGeometryMin, isMin);
} // end setGeometry
/**************************************************************************
* \fn QPoint WeBookSettings::getGeometryPos(const QPoint &thisDefaultValue)
***************************************************************************/
QPoint WeBookSettings::getGeometryPos(const QPoint &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryPos, thisDefaultValue).toPoint();
} // end getGeometryPos
/**************************************************************************
* \fn QSize WeBookSettings::getGeometrySize(const QSize &thisDefaultValue)
***************************************************************************/
QSize WeBookSettings::getGeometrySize(const QSize &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometrySize, thisDefaultValue).toSize();
} // end getGeometrySize
/**************************************************************************
* \fn bool WeBookSettings::getGeometryMax(const bool &thisDefaultValue)
***************************************************************************/
bool WeBookSettings::getGeometryMax(const bool &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryMax, thisDefaultValue).toBool();
} // end getGeometryMax
/**************************************************************************
* \fn bool WeBookSettings::getGeometryMin(const bool &thisDefaultValue)
***************************************************************************/
bool WeBookSettings::getGeometryMin(const bool &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryMin, thisDefaultValue).toBool();
} // end getGeometryMin
/******************************* End of File *********************************/

