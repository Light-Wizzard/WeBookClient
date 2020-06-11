#ifndef WEBOOKCOMMON_H
#define WEBOOKCOMMON_H

#include <QApplication>
#include <QtCore>
#include <QCryptographicHash>
#include <QtGlobal>
#include <QObject>
#include <QDir>
#include <stdio.h>
#include <stdlib.h>
#include <QProcess>

// QLogger
#include "QLogger.h"
// Qt-AES
#include "src/QtAES/QAESEncryption.h"
/******************************************************************************
** class WeBookCommon                                                         *
*******************************************************************************/
class WeBookCommon : public QObject
{
        Q_OBJECT

    public:
        explicit WeBookCommon(bool isLog);
        ~WeBookCommon();
        // I do not like hard coding variables into Applications
        const QString constAppFolder             = "WeBook";           // Name of Folder this Project is in
        const QString constFileFolderName        = "data";             // Name of data Folder
        const QString constLogFolderName         = "logs";             // Name of log Folder
        // Const Ini File Name Full Path if want to change the Path to the ini or rename it, leaving it just the name, will look for it in the data folder
        // normally WeBookClient.ini, but I make it an option, see above comment
        const QString constIniFileName           = "WeBookClient.ini"; // Name of ini file with no path
        //
        const QString constCryptoKey             = "!1@2#3$4%5^6&7*8)9(0)NowPickRand"; // These values are for testing only
        const QString constCryptoIvVector        = "PutMoveVector1!2@3#4$NowPickRand"; // These values are for testing only
        //
        const QString constAppName               = "WeBookClient";
        // These next 3 settings will set the Local Data Storage for this App to use, changing it after it has run, will create a new storage containtainer
        // This is the User Name for GitHub account, but does not have to be
        const QString constOrgName = "Light Wizzard";
        // This is the User Name and Project or GitHub URL, but does not have to be
        const QString constOrgDomain = "https://github.com/Light-Wizzard/WeBookClient";
        // I hard code these values here for a reason, not that I would use them, set the Link to include this data, pass in as Arguments
        // These values are for testing only
        // Default WeBookServer Port
        const quint16 ConstPort                  = 9696; // Port of WeBookServer
        // Store only what you need, comment the rest
        const QString constHomeLocation          = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);          // Home
        const QString constAppDataLocation       = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);       // App Data
//        const QString constDesktopLocation       = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);       // Desktop
//        const QString constDocumentsLocation     = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);     // Documents
//        const QString constDownloadLocation      = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);      // Download
//        const QString constMusicLocation         = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);         // Music
//        const QString constMoviesLocation        = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);        // Movies
//        const QString constPicturesLocation      = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);      // Pictures
//        const QString constDataLocation          = QStandardPaths::writableLocation(QStandardPaths::DataLocation);          // Data
//        const QString constApplicationsLocation  = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);  // Applications
//        const QString constAppLocalDataLocation  = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);  // App Local Data
//        const QString constAppConfigLocation     = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);     // App Config
//        const QString constFontsLocation         = QStandardPaths::writableLocation(QStandardPaths::FontsLocation);         // Fonts
//        const QString constTempLocation          = QStandardPaths::writableLocation(QStandardPaths::TempLocation);          // Temp
//        const QString constCacheLocation         = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);         // Cache
//        const QString constGenericCacheLocation  = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);  // Generic Cache
//        const QString constGenericDataLocation   = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);   // Generic Data
//        const QString constConfigLocation        = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);        // Config
//        const QString constGenericConfigLocation = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation); // Generic Config
//        const QString constRuntimeLocation       = QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation);       // Runtime
/*
Path type               Linux                   macOS                   Windows                                 Android                     iOS
DesktopLocation         "~/Desktop"             "~/Desktop"             "C:/Users/<USER>/Desktop"               "<APPROOT>/files"           "<APPROOT>/Documents/Desktop"
DocumentsLocation       "~/Documents"           "~/Documents"           "C:/Users/<USER>/Documents"             "<USER>/Documents", "<USER>/<APPNAME>/Documents"
                                                                                                                                            "<APPROOT>/Documents"
FontsLocation           "~/.fonts", "~/.local/share/fonts", "/usr/local/share/fonts", "/usr/share/fonts"
                                                "/System/Library/Fonts" (not writable)
                                                                        "C:/Windows/Fonts" (not writable)
                                                                                                                "/system/fonts" (not writable)
                                                                                                                                            "<APPROOT>/Library/Fonts"
ApplicationsLocation    "~/.local/share/applications", "/usr/local/share/applications", "/usr/share/applications"
                                                "/Applications" (not writable)
                                                                        "C:/Users/<USER>/AppData/Roaming/Microsoft/Windows/Start Menu/Programs"
                                                                                                                not supported (directory not readable)
                                                                                                                                            not supported
MusicLocation           "~/Music"               "~/Music"               "C:/Users/<USER>/Music"                 "<USER>/Music", "<USER>/<APPNAME>/Music"
                                                                                                                                            "<APPROOT>/Documents/Music"
MoviesLocation          "~/Videos"              "~/Movies"              "C:/Users/<USER>/Videos"                "<USER>/Movies", "<USER>/<APPNAME>/Movies"
                                                                                                                                            "<APPROOT>/Documents/Movies"
PicturesLocation        "~/Pictures"            "~/Pictures"            "C:/Users/<USER>/Pictures"              "<USER>/Pictures", "<USER>/<APPNAME>/Pictures"
                                                                                                                                            "<APPROOT>/Documents/Pictures", "assets-library://"
TempLocation            "/tmp"                  randomly generated      "C:/Users/<USER>/AppData/Local/Temp"    "<APPROOT>/cache"           "<APPROOT>/tmp"
HomeLocation            "~"                     "~"                     "C:/Users/<USER>"                       "<APPROOT>/files"           system defined
DataLocation            "~/.local/share/<APPNAME>", "/usr/local/share/<APPNAME>", "/usr/share/<APPNAME>"
                                                "~/Library/Application Support/<APPNAME>", "/Library/Application Support/<APPNAME>". "<APPDIR>/../Resources"
                                                                        "C:/Users/<USER>/AppData/Local/<APPNAME>", "C:/ProgramData/<APPNAME>", "<APPDIR>", "<APPDIR>/data", "<APPDIR>/data/<APPNAME>"
                                                                                                                "<APPROOT>/files", "<USER>/<APPNAME>/files"
                                                                                                                                            "<APPROOT>/Library/Application Support"
CacheLocation           "~/.cache/<APPNAME>"
                                                "~/Library/Caches/<APPNAME>", "/Library/Caches/<APPNAME>"
                                                                        "C:/Users/<USER>/AppData/Local/<APPNAME>/cache"
                                                                                                                "<APPROOT>/cache", "<USER>/<APPNAME>/cache"
                                                                                                                                            "<APPROOT>/Library/Caches"
GenericDataLocation     "~/.local/share", "/usr/local/share", "/usr/share"
                                                "~/Library/Application Support", "/Library/Application Support"
                                                                        "C:/Users/<USER>/AppData/Local", "C:/ProgramData", "<APPDIR>", "<APPDIR>/data"
                                                                                                                "<USER>"                    "<APPROOT>/Documents"
RuntimeLocation         "/run/user/<USER>"      "~/Library/Application Support"	"C:/Users/<USER>"               "<APPROOT>/cache"           not supported
ConfigLocation          "~/.config", "/etc/xdg" "~/Library/Preferences"	"C:/Users/<USER>/AppData/Local/<APPNAME>", "C:/ProgramData/<APPNAME>"
                                                                                                                "<APPROOT>/files/settings"  "<APPROOT>/Library/Preferences"
GenericConfigLocation   "~/.config", "/etc/xdg" "~/Library/Preferences"	"C:/Users/<USER>/AppData/Local", "C:/ProgramData"
                                                                                                                "<APPROOT>/files/settings" (there is no shared settings)
                                                                                                                                            "<APPROOT>/Library/Preferences"
DownloadLocation        "~/Downloads"           "~/Downloads"           "C:/Users/<USER>/Documents"             "<USER>/Downloads", "<USER>/<APPNAME>/Downloads"
                                                                                                                                            "<APPROOT>/Documents/Downloads"
GenericCacheLocation    "~/.cache"              "~/Library/Caches", "/Library/Caches"	"C:/Users/<USER>/AppData/Local/cache"
                                                                                                                "<APPROOT>/cache" (!shared) "<APPROOT>/Library/Caches"
AppDataLocation         "~/.local/share/<APPNAME>", "/usr/local/share/<APPNAME>", "/usr/share/<APPNAME>"
                                                "~/Library/Application Support/<APPNAME>", "/Library/Application Support/<APPNAME>". "<APPDIR>/../Resources"
                                                                        "C:/Users/<USER>/AppData/Roaming/<APPNAME>", "C:/ProgramData/<APPNAME>", "<APPDIR>", "<APPDIR>/data", "<APPDIR>/data/<APPNAME>"
                                                                                                                "<APPROOT>/files", "<USER>/<APPNAME>/files"
                                                                                                                                            "<APPROOT>/Library/Application Support"
AppLocalDataLocation    "~/.local/share/<APPNAME>", "/usr/local/share/<APPNAME>", "/usr/share/<APPNAME>"
                                                "~/Library/Application Support/<APPNAME>", "/Library/Application Support/<APPNAME>". "<APPDIR>/../Resources"
                                                                        "C:/Users/<USER>/AppData/Local/<APPNAME>", "C:/ProgramData/<APPNAME>", "<APPDIR>", "<APPDIR>/data", "<APPDIR>/data/<APPNAME>"
                                                                                                                "<APPROOT>/files/settings" "<APPROOT>/Library/Preferences/<APPNAME>"
AppConfigLocation       "~/.config/<APPNAME>", "/etc/xdg/<APPNAME>"
                                                "~/Library/Preferences/<APPNAME>"
                                                                        "C:/Users/<USER>/AppData/Local/<APPNAME>", "C:/ProgramData/<APPNAME>"
                                                                                                                "<APPROOT>/files", "<USER>/<APPNAME>/files"
                                                                                                                                            "<APPROOT>/Library/Application Support"
*/
        // Settings Constants Field names QSettings
        const QString ConstSettingsIniFileName     = "SettingsIniFileName";                 // These values are used for Qt Settings as Literal Strings
        const QString ConstSettingsApplicationName = "SettingsApplicationName";             // It acts like the name in a Database
        const QString ConstSettingsOrgName         = "SettingsOrgName";                     // Settings is a Key (This is the Key) Value that is what gets assigned to this
        const QString ConstSettingsOrgDomain       = "SettingsOrgDomain";                   //
        const QString ConstSettingsGeometryPos     = "SettingsGeometryPos";                 // This holds the Screens Geometry
        const QString ConstSettingsGeometrySize    = "SettingsGeometrySize";                // This holds the Screens Geometry
        const QString ConstSettingsGeometryMax     = "SettingsGeometryMax";                 // This holds the Screens Geometry
        const QString ConstSettingsGeometryMin     = "SettingsGeometryMin";                 // This holds the Screens Geometry
        // Enumerators
        enum PasswordCryptoMd     { PasswordCryptoHashMd4, PasswordCryptoHashMd5 }; // Used for data encyption
        enum PasswordCryptoSha    { PasswordCryptoHashSha1, PasswordCryptoHashSha224, PasswordCryptoHashSha256, PasswordCryptoHashSha384, PasswordCryptoHashSha512, PasswordCryptoHashSha3_224, PasswordCryptoHashSha3_256, PasswordCryptoHashSha3_384, PasswordCryptoHashSha3_512 };
        enum PasswordCryptoKeccak { PasswordCryptoHashKeccak_224, PasswordCryptoHashKeccak_256, PasswordCryptoHashKeccak_384, PasswordCryptoHashKeccak_512 };
        Q_ENUM(PasswordCryptoMd)       // I use MD 4 or 5 as a Seed to AES
        Q_ENUM(PasswordCryptoSha)      // I use SHAx also as a Seed to AES
        Q_ENUM(PasswordCryptoKeccak)   // I am leaving this in, in case I want to use it

        // Note you cannot set the Path by default for cross platform
        QString getFilelPath();                                                             // myFilePath
        void setFilePath(const QString &thisDataFullPath);
        // HomePath
        QString getHomePath();                                                              // myHomePath
        void setHomePath(const QString &thisLogPath);
        // LogPath
        QString getLogPath();                                                               // myLogPath
        void setLogPath(const QString &thisLogPath);
        // Ini File Name
        QString getIniFileName();                                                           // myIniFileName
        void setIniFileName(const QString &thisIniFileName);
        // Organization Name
        QString getOrgName();                                                               // myOrganizationName
        void setOrgName(const QString &thisOrgName);
        // Organization Domain
        QString getOrgDomain();                                                             // myOrganizationDomain
        void setOrgDomain(const QString &thisOrgDomain);
        // Application Name
        QString getAppName();                                                               // myApplicationName
        void setAppName(const QString &thisAppName);
        // UserName
        QString getUserName();                                                               // myUserName
        void setUserName(const QString &thisUserName);
        // QSetter
        void weBookSetter();                                                                // QSetter
        bool     isSetting(const QString &thisCryptoKey);                                   // isSetting
        void     setSetting(const QString &thisKey, const QVariant &thisValue);             // setSetting
        QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant()); // getSetting
        // Crypto Key
        QString getCryptoKey();                                                             // myCryptoKey
        void setCryptoKey(const QString &thisCryptoKey);
        // Crypto IV Vector
        QString getCryptoIvVector();                                                        // myCryptoIvVector
        void setCryptoIvVector(const QString &thisCryptoIvVector);
        // Crypto
        QString getMd();                                                                    // PasswordCryptoMd     myCryptoMd
        QString getSha();                                                                   // PasswordCryptoSha    myCryptoSha
        QString getKeccak(const QString &thisIvVector);                                     // PasswordCryptoKeccak myCryptoKeccak
        QString enCodeSecret(const QString &thisSecretString);                              // enCode Secret AES
        QString deCodeSecret(const QString &thisSecretString);                              // deCode Secret AES
        void setCryptoCodeHashish();                                                        // set Crypto Code Hashish (Hash Like: combines both cryptoKey and cryptoIvVector, to form AES Encrytion)
        // Port of WeBookServer
        quint16 getPort();                                                                  // myPort
        void setPort(quint16 thisPort);
        // Logger
        void setWeBookLogger();
        //
        QString setFilePath(QString thisFileName, QString thisDataFolderName);              //
        //
        QString combinePathFileName(QString thisPath, QString thisFileName);                //
        // Screen Geometry
        void     setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin);       // Screen Geometry
        QVariant getGeometryPos(const QPoint &thisDefaultValue);
        QVariant getGeometrySize(const QSize &thisDefaultValue);
        bool     getGeometryMax(const bool &thisDefaultValue);
        bool     getGeometryMin(const bool &thisDefaultValue);
        // File and Path
        bool isFileExists(QString thisFile);                                                // File Functions
        bool isPathExists(QString thisPath);
        bool isPathMake(const QString &thisRootPath, const QString &thisPath);
        QString getFullFilePathName(QString thisFileName);
        bool isMakeDir(const QString &thisPath);
        //
        QString getLogFolderName();
        void setLogFolderName(const QString &thisLogFolderName);
        //
        QString getFileFolderName();
        void setFileFolderName(const QString &thisFileFolderName);        
        bool isFileMake(const QString &thisPath, const QString &thisFileName);

    signals:
        void handelSettinChanged();

    private:
        QSettings               *weBookSettings         = nullptr;                          // QSettings is used for this class
        QString                 myLogPath               = "";                               //
        QString                 myLogFolderName         = "";                               //
        QString                 myFilePath              = "";                               // Path to the folder that holds the data, I named it data by default
        QString                 myFileFolderName        = "";                               // File Folder Name
        QString                 myHomePath              = "";                               //
        QString                 myUserName              = "";                               //
        QString                 myIniFileName           = "";                               // Ini File Name
        QString                 myOrganizationName      = "";                               // OrganizationName
        QString                 myOrganizationDomain    = "";                               // OrganizationDomain
        QString                 myApplicationName       = "";                               // ApplicationName
        QString                 myCryptoKey             = "";                               // Argument to Constructor from main.cpp
        QString                 myCryptoIvVector        = "";                               // Argument to Constructor from main.cpp
        PasswordCryptoMd        myCryptoMd              = PasswordCryptoHashMd5;            // PasswordCryptoHashMd4, PasswordCryptoHashMd5
        PasswordCryptoSha       myCryptoSha             = PasswordCryptoHashSha3_512;       // PasswordCryptoHashSha1, PasswordCryptoHashSha224, PasswordCryptoHashSha256, PasswordCryptoHashSha384, PasswordCryptoHashSha512, PasswordCryptoHashSha3_224, PasswordCryptoHashSha3_256, PasswordCryptoHashSha3_384, PasswordCryptoHashSha3_512
        PasswordCryptoKeccak    myCryptoKeccak          = PasswordCryptoHashKeccak_512;     // PasswordCryptoHashKeccak_224, PasswordCryptoHashKeccak_256, PasswordCryptoHashKeccak_384, PasswordCryptoHashKeccak_512
        QByteArray              myHashKey;                                                  // used for Encryption and Decrytion
        QByteArray              myHashIV;                                                   // used for Encryption and Decrytion
        quint16                 myPort                  = 0;                                // Port Number of WeBookServer
        QLogger::QLoggerManager *manager                = nullptr;
}; // end class WeBookCommon
#endif // WEBOOKCOMMON_H
/* ***************************** End of File ******************************* */
