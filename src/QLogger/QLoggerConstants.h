#pragma once
#ifndef QLOGGERCONSTANTS_H
#define QLOGGERCONSTANTS_H
#include <QtCore>
#include <QString>
/******************************************************************************
* QLogger                                                                    *
* Thread-safe logger for Qt applications                                     *
* https://github.com/francescmm/QLogger                                      *
* Fork: https://github.com/Light-Wizzard/QLogger                             *
* This is where all the hard coded variables the App needs to run            *
* This Project is GitHub Based, and can use GitHub features if Enabled       *
* To make this Project flexible it is configuration here                     *
* There are a lot of notes about paths in this header, its cross-plateform   *
*******************************************************************************/
namespace QLogger
{
    //
    const QString ConstDefaultAppName               = "WeBookClient";     //!< \c ConstDefaultAppName           \brief Default App Name.
    const QString ConstDefaultOrgName               = "Light-Wizzard";    //!< \c ConstDefaultOrgName           \brief Default Org Name.
    const QString ConstDefaultAppFolder             = "WeBook";           //!< \c ConstDefaultAppFolder         \brief Default Name of Folder this Project is in.
    const QString ConstDefaultFileFolderName        = "data";             //!< \c ConstDefaultFileFolderName    \brief Default Name of data file Folder.
    const QString ConstDefaultLogFolderName         = "logs";             //!< \c ConstDefaultLogFolderName     \brief Default Name of log Folder.
    const QString ConstDefaultLogFileExtension      = "log";              //!< \c ConstDefaultLogFileExtension  \brief Default Log File Extension.
    // Const Ini File Name Full Path if want to change the Path to the ini or rename it, leaving it just the name, will look for it in the data folder
    // normally Settings.ini, but I make it an option, see above comment
    const QString ConstDefaultIniFileName           = "WeBookClient.ini"; //!< \c ConstDefaultIniFileName   \brief Default Ini File Name, Name of ini file with no path.
    // These next 3 settings will set the Local Data Storage for this App to use, changing it after it has run, will create a new storage containtainer
    // This is the User Name for GitHub account, but does not have to be
    // https://github.com/constOrgName/constAppName
    // This is the User Name and Project or GitHub URL, but does not have to be
    const QString ConstDefaultDomain                = "https://github.com"; //!< \c ConstDefaultDomain      \brief Default Domain, This can be any URL.
    // "https://github.com/Light-Wizzard/WeBookClient";
    const QString ConstDefaultOrgDomain             = ConstDefaultDomain + "/" + ConstDefaultOrgName + "/" + ConstDefaultAppName; //!< \c ConstDefaultOrgDomain \brief Default Org Domain .
    // I hard code these values here for a reason, not that I would use them, set the Link to include this data, pass in as Arguments
    // These values are for testing only
    // Default Log Server Port
    const quint16 ConstDefaultPort                  = 9696;             //!< \c ConstDefaultPort            \brief Port Number of Log Server.
    const QString ConstDefaultLogNamePattern        = "-Log.yyyy-MM";   //!< \c ConstDefaultLogNamePattern  \brief Log File Name Pattern (See Notes in QLoggerCommon.h).
    const QString ConstDefaultModuleName            = "WeBook";         //!< \c ConstDefaultModuleName      \brief Default Module Name.
    const QPoint  ConstDefaultGeometryPos           = QPoint(10, 10);   //!< \c ConstDefaultGeometryPos     \brief Top, Left.
    const QSize   ConstDefaultGeometrySize          = QSize(1000, 666); //!< \c ConstDefaultGeometrySize    \brief Width x Height.
    const QString ConstDefaultCryptoKey             = "!1@2#3$4%5^6&7*8)9(0)NowPickRand"; //!< \c ConstDefaultCryptoKey      \brief Default Crypto Key these values are for testing only.
    const QString ConstDefaultCryptoIvVector        = "PutMoveVector1!2@3#4$NowPickRand"; //!< \c ConstDefaultCryptoIvVector \brief Default Crypto IV Vector these values are for testing only.

    const QString ConstDefaultWeBookTOCName         = "WeBook.toc";       //!< \c ConstDefaultWeBookTOCName \brief Name of toc file for default WeBook TOC.
    const QString ConstDefaultWeBookCatName         = "WeBooks.cat";      //!< \c ConstDefaultWeBookCatName \brief Name of WeBook Category file for default WeBook.

    // Store only what you need, comment the rest
    const QString ConstDefaultHomeLocation          = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);          //!< \c ConstDefaultHomeLocation             \brief Path to Home.
    const QString ConstDefaultAppDataLocation       = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);       //!< \c ConstDefaultAppDataLocation          \brief Path to App Data.
    /*
    const QString ConstDefaultDesktopLocation       = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);       //!< \c ConstDefaultDesktopLocation          \brief Path to Desktop
    const QString ConstDefaultDocumentsLocation     = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);     //!< \c ConstDefaultDocumentsLocation        \brief Path to Documents
    const QString ConstDefaultDownloadLocation      = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);      //!< \c ConstDefaultDownloadLocation         \brief Path to Download
    const QString ConstDefaultMusicLocation         = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);         //!< \c ConstDefaultMusicLocation            \brief Path to Music
    const QString ConstDefaultMoviesLocation        = QStandardPaths::writableLocation(QStandardPaths::MoviesLocation);        //!< \c ConstDefaultMoviesLocation           \brief Path to Movies
    const QString ConstDefaultPicturesLocation      = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);      //!< \c ConstDefaultPicturesLocation         \brief Path to Pictures
    const QString ConstDefaultDataLocation          = QStandardPaths::writableLocation(QStandardPaths::DataLocation);          //!< \c ConstDefaultDataLocation             \brief Path to Data
    const QString ConstDefaultApplicationsLocation  = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation);  //!< \c ConstDefaultApplicationsLocation     \brief Path to Applications
    const QString ConstDefaultAppLocalDataLocation  = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);  //!< \c ConstDefaultAppLocalDataLocation     \brief Path to App Local Data
    const QString ConstDefaultAppConfigLocation     = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);     //!< \c ConstDefaultAppConfigLocation        \brief Path to App Config
    const QString ConstDefaultFontsLocation         = QStandardPaths::writableLocation(QStandardPaths::FontsLocation);         //!< \c ConstDefaultFontsLocation            \brief Path to Fonts
    const QString ConstDefaultTempLocation          = QStandardPaths::writableLocation(QStandardPaths::TempLocation);          //!< \c ConstDefaultTempLocation             \brief Path to Temp
    const QString ConstDefaultCacheLocation         = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);         //!< \c ConstDefaultCacheLocation            \brief Path to Cache
    const QString ConstDefaultGenericCacheLocation  = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation);  //!< \c ConstDefaultGenericCacheLocation     \brief Path to Generic Cache
    const QString ConstDefaultGenericDataLocation   = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);   //!< \c ConstDefaultGenericDataLocation      \brief Path to Generic Data
    const QString ConstDefaultConfigLocation        = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);        //!< \c ConstDefaultConfigLocation           \brief Path to Config
    const QString ConstDefaultGenericConfigLocation = QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation); //!< \c ConstDefaultGenericConfigLocation    \brief Path to Generic Config
    const QString ConstDefaultRuntimeLocation       = QStandardPaths::writableLocation(QStandardPaths::RuntimeLocation);       //!< \c ConstDefaultRuntimeLocation          \brief Path to Runtime
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
    // Settings is a Key (This is the Key) Value that is what gets assigned to this
    // These values are used for Qt Settings as Literal Strings
    //  It acts like the name in a Database
    const QString ConstSettingsModuelName      = "SettingsModuelName";      //!< \c ConstSettingsModuelName      \brief QSettings Field Settings Moduel Name.
    const QString ConstSettingsIniFileName     = "SettingsIniFileName";     //!< \c ConstSettingsIniFileName     \brief QSettings Field Settings Ini File Name.
    const QString ConstSettingsApplicationName = "SettingsApplicationName"; //!< \c ConstSettingsApplicationName \brief QSettings Field Settings Application Name.
    const QString ConstSettingsOrgName         = "SettingsOrgName";         //!< \c ConstSettingsOrgName         \brief QSettings Field Settings Org Name.
    const QString ConstSettingsOrgDomain       = "SettingsOrgDomain";       //!< \c ConstSettingsOrgDomain       \brief QSettings Field Settings Org Domain.
    const QString ConstSettingsGeometryPos     = "SettingsGeometryPos";     //!< \c ConstSettingsGeometryPos     \brief QSettings Field Settings Geometry Pos.
    const QString ConstSettingsGeometrySize    = "SettingsGeometrySize";    //!< \c ConstSettingsGeometrySize    \brief QSettings Field Settings Geometry Size.
    const QString ConstSettingsGeometryMax     = "SettingsGeometryMax";     //!< \c ConstSettingsGeometryMax     \brief QSettings Field Settings Geometry Max.
    const QString ConstSettingsGeometryMin     = "SettingsGeometryMin";     //!< \c ConstSettingsGeometryMin     \brief QSettings Field Settings Geometry Min.
    const QString ConstSettingsPort            = "SettingsPort";            //!< \c ConstSettingsPort            \brief QSettings Field Settings Port Number to Log Server.
    const QString ConstSettingsLogFolder       = "SettingsLogFolder";       //!< \c ConstSettingsLogFolder       \brief QSettings Field Settings Log Folder.
    const QString ConstSettingsLogNamePattern  = "SettingsLogNamePattern";  //!< \c ConstSettingsLogNamePattern  \brief QSettings Field Settings Log Name Pattern.
    const QString ConstSettingsFileFolder      = "SettingsFileFolder";      //!< \c ConstSettingsFileFolder      \brief QSettings Field Settings File Folder.
    const QString ConstSettingsLogFileExt      = "SettingsLogFileExt";      //!< \c ConstSettingsLogFileExt      \brief QSettings Field Settings Log File Ext.

} // end namespace QLogger
#endif // QLOGGERCONSTANTS_H
/******************************* End of File *********************************/

