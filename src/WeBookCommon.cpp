/******************************************************************************
** WeBook: Pronounced Web-Book, is a Book Content Management System  (BCMS)   *
*******************************************************************************/
#include "WeBookCommon.h"
/******************************************************************************
** WeBookCommon Constructor                                                   *
** Requires Setting:
** OrganizationName
** OrganizationDomain
** ApplicationName
*******************************************************************************/
WeBookCommon::WeBookCommon(bool isLog)
{
    if (isLog) setWeBookLogger();
} // end WeBookCommon
/******************************************************************************
** WeBookCommon Deconstructor                                                 *
*******************************************************************************/
WeBookCommon::~WeBookCommon()
{

} // end ~WeBookCommon
/******************************************************************************
** weBookSetter                                                               *
** Creates QSettings for organizationName, organizationDomain, applicationName*
**
*******************************************************************************/
void WeBookCommon::weBookSetter()
{
    // organizationName, organizationDomain, applicationName and applicationName
    // are set in main.cpp, and passed into Constuctor, so they are set
    QApplication::setOrganizationName(getOrgName());
    QApplication::setOrganizationDomain(getOrgDomain());
    QApplication::setApplicationName(getAppName());
    QApplication::setApplicationDisplayName(getAppName());
    // see *.pro file where it is: DEFINE  S     *= APP_VERSION=$${VERSION}
    QApplication::setApplicationVersion(QObject::tr(APP_VERSION));
    QString myIni = getFullFilePathName(getIniFileName());

    if (!isFileMake(getFilelPath(), getIniFileName()))
    {
        qFatal("%s", QString("Error: cannot create file %1").arg(myIni).toLocal8Bit().constData());
    }
    weBookSettings  = new QSettings(myIni, QSettings::IniFormat);
} // end weBookSetter
/******************************************************************************
** combinePathFileName                                                        *
*******************************************************************************/
QString WeBookCommon::combinePathFileName(QString thisPath, QString thisFileName)
{
    return QString("%1%2%3").arg(thisPath).arg(QDir::separator()).arg(thisFileName);
} // end combinePathFileName
/******************************************************************************
** isFileExists                                                               *
*******************************************************************************/
bool WeBookCommon::isFileExists(QString thisFile)
{
    // check if file exists and if yes: Is it really a file and not directory?
    return QFileInfo::exists(thisFile) && QFileInfo(thisFile).isFile();
} // end isFileExists
/******************************************************************************
** isFileMake                                                                 *
*******************************************************************************/
bool WeBookCommon::isFileMake(const QString &thisPath, const QString &thisFileName)
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
bool WeBookCommon::isPathExists(QString thisPath)
{
    return QDir(thisPath).exists();
} // end isPathExists
/******************************************************************************
** isPathMake                                                                 *
*******************************************************************************/
bool WeBookCommon::isPathMake(const QString &thisRootPath, const QString &thisPath)
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
bool WeBookCommon::isMakeDir(const QString &thisPath)
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
bool WeBookCommon::isSetting(const QString &thisCryptoKey)
{
    if (weBookSettings == nullptr)  weBookSetter();
    return weBookSettings->contains(thisCryptoKey);
} // end isSetting
/******************************************************************************
** getSetting by key and  default Value                                       *
** QString myName = getSetting("key", "default value");                       *
*******************************************************************************/
QVariant WeBookCommon::getSetting(const QString &key, const QVariant &defaultValue)
{
    if (weBookSettings == nullptr) weBookSetter();
    if (! isSetting(key))
    {
        setSetting(key, defaultValue);
        return defaultValue;
    }
    qDebug() << "getSettings=" << weBookSettings->value(key, defaultValue);
    return weBookSettings->value(key, defaultValue);
} // end getSetting
/******************************************************************************
** setSetting using key and settingValue                                      *
** setSetting("this_key", "to this");                                         *
** QVariant is used for value, so it can be anything it supports              *
*******************************************************************************/
void WeBookCommon::setSetting(const QString &thisKey, const QVariant &thisValue)
{
    if (weBookSettings == nullptr) weBookSetter();
    weBookSettings->setValue(thisKey, thisValue);
} // end setSetting
/******************************************************************************
** getOrgName                                                                 *
** This value is used for Qt Settings: GitHub Account Name is one example     *
*******************************************************************************/
QString WeBookCommon::getOrgName()
{
    if (myOrganizationName.isEmpty()) myOrganizationName = constOrgName;
    return myOrganizationName;
} // end getOrgName
/******************************************************************************
** setOrgName(myValue)                                                        *
*******************************************************************************/
void WeBookCommon::setOrgName(const QString &thisOrgName)
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
QString WeBookCommon::getOrgDomain()
{
    if (myOrganizationName.isEmpty()) myOrganizationDomain = constOrgDomain;
    return myOrganizationDomain;
} // end getOrgDomain
/******************************************************************************
** setOrgDomain(myValue)                                                      *
*******************************************************************************/
void WeBookCommon::setOrgDomain(const QString &thisOrgDomain)
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
QString WeBookCommon::getAppName()
{
    if (myApplicationName.isEmpty()) myApplicationName = constAppName;
    return myApplicationName;
} // end getAppName
/******************************************************************************
** setAppName(myValue)                                                        *
*******************************************************************************/
void WeBookCommon::setAppName(const QString &thisAppName)
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
QString WeBookCommon::getIniFileName()
{
    if (myIniFileName.isEmpty()) myIniFileName = constIniFileName;
    return myIniFileName;
} // end getIniFileName
/******************************************************************************
** setIniFileName                                                             *
*******************************************************************************/
void WeBookCommon::setIniFileName(const QString &thisIniFileName)
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
QString WeBookCommon::getLogPath()
{
    if (myLogPath.isEmpty()) myLogPath = QString("%1%2%3%4%5").arg(getHomePath()).arg(QDir::separator()).arg(getAppName()).arg(QDir::separator()).arg(getLogFolderName());

    if (!isMakeDir(QString("%1%2%3").arg(getHomePath()).arg(QDir::separator()).arg(getAppName())))
    {
        qFatal("%s", QString("Error: cannot create Folder %1").arg(QString("%1%2%3").arg(getHomePath()).arg(QDir::separator()).arg(getAppName())).toLocal8Bit().constData());
    }
    if (!isMakeDir(QString("%1%2%3%4%5").arg(getHomePath()).arg(QDir::separator()).arg(getAppName()).arg(QDir::separator()).arg(getLogFolderName())))
    {
        qFatal("%s", QString("Error: cannot create Folder %1").arg(QString("%1%2%3%4%5").arg(getHomePath()).arg(QDir::separator()).arg(getAppName()).arg(QDir::separator()).arg(getLogFolderName())).toLocal8Bit().constData());
    }
    return myLogPath;
} // end getLogPath
/******************************************************************************
** setLogPath                                                                 *
*******************************************************************************/
void WeBookCommon::setLogPath(const QString &thisLogPath)
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
QString WeBookCommon::getLogFolderName()
{
    if (myLogFolderName.isEmpty()) myLogFolderName = constLogFolderName;
    return myLogFolderName;
} // end getLogFolderName
/******************************************************************************
** setLogFolderName                                                           *
*******************************************************************************/
void WeBookCommon::setLogFolderName(const QString &thisLogFolderName)
{
    if (myLogFolderName != thisLogFolderName)
    {
        myLogFolderName = thisLogFolderName;
        emit handelSettinChanged();
    }
} // end setLogFolderName
/******************************************************************************
** getFileFolderName                                                          *
*******************************************************************************/
QString WeBookCommon::getFileFolderName()
{
    if (myFileFolderName.isEmpty()) myFileFolderName = constFileFolderName;
    return myFileFolderName;
} // end getFileFolderName
/******************************************************************************
** setFileFolderName                                                          *
*******************************************************************************/
void WeBookCommon::setFileFolderName(const QString &thisFileFolderName)
{
    if (myFileFolderName != thisFileFolderName)
    {
        myFileFolderName = thisFileFolderName;
        emit handelSettinChanged();
    }
} // end setFileFolderName
/******************************************************************************
** getFilelPath                                                               *
** /constDataFolderName/
*******************************************************************************/
QString WeBookCommon::getFilelPath()
{
    if (myFilePath.isEmpty()) myFilePath = QString("%1%2%3%4%5").arg(getHomePath()).arg(QDir::separator()).arg(getAppName()).arg(QDir::separator()).arg(getFileFolderName());
    return myFilePath;
} // end getFilelPath
/******************************************************************************
** setFilePath                                                                *
*******************************************************************************/
void WeBookCommon::setFilePath(const QString &thisDataFullPath)
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
QString WeBookCommon::getHomePath()
{
    if (myHomePath.isEmpty()) myHomePath = constHomeLocation;
    return myHomePath;
} // end getHomePath
/******************************************************************************
** setHomePath                                                                *
*******************************************************************************/
void WeBookCommon::setHomePath(const QString &thisHomePath)
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
QString WeBookCommon::getUserName()
{
    if (myUserName.isEmpty()) setUserName("");
    return myUserName;
} // end getUserName
/******************************************************************************
** setUserName                                                                *
*******************************************************************************/
void WeBookCommon::setUserName(const QString &thisUserName)
{
    if (myUserName.isEmpty() || thisUserName.isEmpty())
    {
        myUserName = qgetenv("USER");
        if (myUserName.isEmpty()) myUserName = qgetenv("USERNAME");
        if (myUserName.isEmpty())
        {
        #if   defined(Q_OS_ANDROID)
        #elif defined(Q_OS_BLACKBERRY)
        #elif defined(Q_OS_IOS)
        #elif defined(Q_OS_MAC)
        #elif defined(Q_OS_WINCE)
        #elif defined(Q_OS_WIN)
//            if (myUserName.isEmpty())
//            {
//                char acUserName[MAX_USERNAME];
//                DWORD nUserName = sizeof(acUserName);
//                if (GetUserName(acUserName, &nUserName)) myUserName = acUserName;
//            }
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
** getPort                                                                    *
** Valid Port Numbers range varies on plateform                               *
** Typical Ports: 8080                                                        *
*******************************************************************************/
quint16 WeBookCommon::getPort()
{
    if (myPort == 0) myPort = ConstPort;
    return myPort;
} // end getPort
/******************************************************************************
** setPort(int thisPort)                                                      *
*******************************************************************************/
void WeBookCommon::setPort(quint16 thisPort)
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
QString WeBookCommon::setFilePath(QString thisFileName, QString thisDataFolderName)
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
    QString dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("%1%2%3").arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName)));
    // If ran from within Qt Creator
    if (!dataFullPath.contains(constAppFolder))
    {
        // APP_FOLDER/databaseFolderName/databaseFileName
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1%2%3%4%5%6").arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName)));
        qDebug() << QString("..%1%2%3%4%5%6").arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName);
    }
    if (!QFile(dataFullPath).exists())
    {
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2%3%4%5%6%7").arg(QDir::separator()).arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName)));
        qDebug() << QString("..%1..%2%3%4%5%6%7").arg(QDir::separator()).arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName);
    }
    if (!QFile(dataFullPath).exists())
    {
        dataFullPath = dataFileDir.cleanPath(dataFileDir.absoluteFilePath(QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator()).arg(QDir::separator()).arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName)));
        qDebug() << QString("..%1..%2..%3%4%5%6%7%8").arg(QDir::separator()).arg(QDir::separator()).arg(QDir::separator()).arg(constAppFolder).arg(QDir::separator()).arg(thisDataFolderName).arg(QDir::separator()).arg(thisFileName);
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
QString WeBookCommon::getFullFilePathName(QString thisFileName)
{
    return QString("%1%2%3").arg(getFilelPath()).arg(QDir::separator()).arg(getAppName()).arg(QDir::separator()).arg(thisFileName);
} // end getFullFilePathName
/******************************************************************************
** setGeometry                                                                *
*******************************************************************************/
void WeBookCommon::setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin)
{
    setSetting(ConstSettingsGeometryPos, thisPos);
    if(!isMax && !isMin) setSetting(ConstSettingsGeometrySize, thisSize);
    setSetting(ConstSettingsGeometryMax, isMax);
    setSetting(ConstSettingsGeometryMin, isMin);
} // end setGeometry
/******************************************************************************
** getGeometryPos                                                             *
*******************************************************************************/
QVariant WeBookCommon::getGeometryPos(const QPoint &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryPos, thisDefaultValue);
} // end getGeometryPos
/******************************************************************************
** getGeometrySize                                                            *
*******************************************************************************/
QVariant WeBookCommon::getGeometrySize(const QSize &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometrySize, thisDefaultValue);
} // end getGeometrySize
/******************************************************************************
** getGeometryMax                                                             *
*******************************************************************************/
bool WeBookCommon::getGeometryMax(const bool &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryMax, thisDefaultValue).toBool();
} // end getGeometryMax
/******************************************************************************
** getGeometryMin                                                             *
*******************************************************************************/
bool WeBookCommon::getGeometryMin(const bool &thisDefaultValue)
{
    return getSetting(ConstSettingsGeometryMin, thisDefaultValue).toBool();
} // end getGeometryMin
/******************************************************************************
** enCodeSecret(const QString &mySecretString)                                *
*******************************************************************************/
QString WeBookCommon::enCodeSecret(const QString &thisSecretString)
{
    setCryptoCodeHashish();
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    //
    QByteArray encodeText = encryption.encode(thisSecretString.toLocal8Bit(), myHashKey, myHashIV);
    return encodeText;
} // end enCodeSecret
/******************************************************************************
** deCodeSecret(const QString &mySecretString)                                *
*******************************************************************************/
QString WeBookCommon::deCodeSecret(const QString &thisSecretString)
{
    setCryptoCodeHashish();
    QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
    //
    QByteArray decodeText = encryption.decode(thisSecretString.toUtf8(), myHashKey, myHashIV);
    QString decodedString = QString(encryption.removePadding(decodeText));
    return decodedString;
} // end deCodeSecret
/******************************************************************************
** setCryptoCodeHashish                                                       *
*******************************************************************************/
void WeBookCommon::setCryptoCodeHashish()
{
    getSha();
    getSha();
} // end setCryptoCodeHashish
/******************************************************************************
** getCryptoKey                                                               *
*******************************************************************************/
QString WeBookCommon::getCryptoKey()
{
    if (myCryptoKey.isEmpty()) myCryptoKey = constCryptoKey;
    return myCryptoKey;
} // end getCryptoKey
/******************************************************************************
** setCryptoKey(QString myCrypokey)                                           *
*******************************************************************************/
void WeBookCommon::setCryptoKey(const QString &thisCryptoKey)
{
    if (!myCryptoKey.isEmpty() && myCryptoKey != thisCryptoKey)
    {
        myCryptoKey = thisCryptoKey;
    }
} // end setCryptoKey
/******************************************************************************
** getCryptoIvVector                                                          *
*******************************************************************************/
QString WeBookCommon::getCryptoIvVector()
{
    if (myOrganizationName.isEmpty()) myOrganizationName = constOrgName;
    return myCryptoIvVector;
} // end getCryptoIvVector
/******************************************************************************
** setCryptoIvVector(QString myCrypokey)                                      *
*******************************************************************************/
void WeBookCommon::setCryptoIvVector(const QString &thisCryptoIvVector)
{
    if (!myCryptoIvVector.isEmpty() && myCryptoIvVector != thisCryptoIvVector)
    {
        myCryptoIvVector = thisCryptoIvVector;
    }
} // end setCryptoIvVector
/******************************************************************************
** getKeccak                                                                  *
*******************************************************************************/
QString WeBookCommon::getKeccak(const QString &thisIvVector)
{
    QString securePassword;
    switch (myCryptoKeccak)
    {
        case PasswordCryptoHashKeccak_224:
            securePassword = QString(QCryptographicHash::hash((thisIvVector.toUtf8()),QCryptographicHash::Keccak_224).toHex());
            break;
        case PasswordCryptoHashKeccak_256:
            securePassword = QString(QCryptographicHash::hash((thisIvVector.toUtf8()),QCryptographicHash::Keccak_256).toHex());
            break;
        case PasswordCryptoHashKeccak_384:
            securePassword = QString(QCryptographicHash::hash((thisIvVector.toUtf8()),QCryptographicHash::Keccak_384).toHex());
            break;
        case PasswordCryptoHashKeccak_512:
            securePassword = QString(QCryptographicHash::hash((thisIvVector.toUtf8()),QCryptographicHash::Keccak_512).toHex());
            break;
    }
    return securePassword;
} // end getKeccak
/******************************************************************************
** getMd                                                                      *
** Constant
QCryptographicHash::Md4
QCryptographicHash::Md5
*******************************************************************************/
QString WeBookCommon::getMd()
{
    QString securePassword;
    switch (myCryptoMd)
    {
        case PasswordCryptoHashMd4:
            securePassword = QString(QCryptographicHash::hash((myCryptoKey.toUtf8()), QCryptographicHash::Md4).toHex());
            myHashIV         = QCryptographicHash::hash(myCryptoIvVector.toLocal8Bit(), QCryptographicHash::Md4);
            break;
        case PasswordCryptoHashMd5:
            securePassword = QString(QCryptographicHash::hash((myCryptoKey.toUtf8()), QCryptographicHash::Md5).toHex());
            myHashIV         = QCryptographicHash::hash(myCryptoIvVector.toLocal8Bit(), QCryptographicHash::Md5);
            break;
    }
    return securePassword;
} // end getMd
/******************************************************************************
** getSha                                                                     *
** Constant
QCryptographicHash::Sha1
QCryptographicHash::Sha224
QCryptographicHash::Sha256
QCryptographicHash::Sha384
QCryptographicHash::Sha512
QCryptographicHash::Sha3_224
QCryptographicHash::Sha3_256
QCryptographicHash::Sha3_384
QCryptographicHash::Sha3_512
*******************************************************************************/
QString WeBookCommon::getSha()
{
    QString securePassword;
    switch (myCryptoSha)
    {
        case PasswordCryptoHashSha1:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha1).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha1);
            break;
        case PasswordCryptoHashSha224:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha224).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha224);
            break;
        case PasswordCryptoHashSha256:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha256).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha256);
            break;
        case PasswordCryptoHashSha384:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha384).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha384);
            break;
        case PasswordCryptoHashSha512:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha512).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha512);
            break;
        case PasswordCryptoHashSha3_224:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha3_224).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha3_224);
            break;
        case PasswordCryptoHashSha3_256:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha3_256).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha3_256);
            break;
        case PasswordCryptoHashSha3_384:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha3_384).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha3_384);
            break;
        case PasswordCryptoHashSha3_512:
            securePassword = QString(QCryptographicHash::hash((myCryptoIvVector.toUtf8()), QCryptographicHash::Sha3_512).toHex());
            myHashKey        = QCryptographicHash::hash(myCryptoKey.toLocal8Bit(),           QCryptographicHash::Sha3_512);
            break;
    }
    return securePassword;
} // end getSha
/******************************************************************************
** setWeBookLogger                                                            *
*******************************************************************************/
void WeBookCommon::setWeBookLogger()
{
    //qDebug() << "getLogPath=" << getLogPath() << " QDir::separator()=" << QDir::separator() << " date=" << QDateTime::currentDateTime().toString("-Log.yyyy-MM");

    QLogger::myLogFile = QString("%1%2%3.log").arg(getLogPath()).arg(QDir::separator()).arg(getAppName()).arg(QDateTime::currentDateTime().toString("-Log.yyyy-MM"));
    QLogger::myModule = "WeBookServer";

    manager = QLogger::QLoggerManager::getInstance();
    manager->addDestination(QLogger::myLogFile, QLogger::myModule, QLogger::LogLevel::Debug);

    qDebug() << "setWeBookLogger";
} // end setWeBookLogger
/* ***************************** End of File ******************************* */
