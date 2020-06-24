#pragma once

#ifndef QLOGGERCOMMON_H
#define QLOGGERCOMMON_H
/******************************************************************************
 * QLogger is a library to register and print logs into a file.
 **
 * Notes on format for Log File Names:
 * Format	        Result
 * dd.MM.yyyy	    21.05.2001
 * ddd MMMM d yy	Tue May 21 01
 * hh:mm:ss.zzz	14:13:09.120
 * hh:mm:ss.z	    14:13:09.12
 * h:m:s ap	    2:13:9 pm
 *****************************************************************************/

#include <QCoreApplication>
#include <QtCore>
// QLogger Constants
#include "QLoggerConstants.h"
#include "QLoggerLevel.h"
#include "QLoggerManager.h"

/******************************************************************************
* namespace QLogger                                                          *
*******************************************************************************/
namespace QLogger
{
    /**************************************************************************
    * class QLoggerCommon                                                    *
    ***************************************************************************/
    class QLoggerCommon : public QObject
    {
            Q_OBJECT
            //Q_DISABLE_COPY(QLoggerCommon)

        public:
            explicit QLoggerCommon(bool isLog);
            ~QLoggerCommon();
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
            QString getUserName();                                                              // myUserName
            void setUserName(const QString &thisUserName);
            //
            QString getPassword();                                                              // myPassword
            void setPassword(const QString &thisPassword);
            //
            QString getUrl();                                                                   // myUrl
            void setUrl(const QString &thisUrl);
            // QSetter
            void qSettingsInstance();                                                           // QSetter
            bool     isSetting(const QString &thisFieldName);                                   // isSetting
            void     setSetting(const QString &thisKey, const QVariant &defaultValue);          // setSetting
            QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant()); // getSetting
            // Port of Log Server
            quint16 getPort();                                                                  // myPort
            QString portToString();
            void setPort(quint16 thisPort);
            // Logger Manager
            QLoggerManager *getLoggerManager();                                                 // myLoggerManager
            void setLogger();
            //
            QString setFilePath(QString thisFileName, QString thisDataFolderName);              //
            //
            QString combinePathFileName(QString thisPath, QString thisFileName);                //
            // Screen Geometry
            void     setGeometry(QPoint thisPos, QSize thisSize, bool isMax, bool isMin);       // Screen Geometry
            QPoint   getGeometryPos(const QPoint &thisDefaultValue);
            QSize    getGeometrySize(const QSize &thisDefaultValue);
            bool     getGeometryMax(const bool &thisDefaultValue);
            bool     getGeometryMin(const bool &thisDefaultValue);
            // File and Path
            bool isFileExists(QString thisFile);                                                // File Functions
            bool isFileMake(const QString &thisPath, const QString &thisFileName);
            bool isPathExists(QString thisPath);
            bool isPathMake(const QString &thisRootPath, const QString &thisPath);
            QString getFullFilePathName(QString thisFileName);
            bool isMakeDir(const QString &thisPath);
            //
            QString getLogFolderName();                                                         // myLogFolderName
            void setLogFolderName(const QString &thisLogFolderName);
            // Log File Name
            QString getLogFileName();                                                           // myLogFileName
            void setLogFileName(const QString &thisLogFileName);
            // Log File Name Pattern
            QString getLogNamePattern();                                                        // myLogNamePattern
            void setLogNamePattern(const QString &thisLogNamePattern);
            // Log File Extension
            QString getLogFileExtension();                                                      // myLogFileExtension
            void setLogFileExtension(const QString &thisLogFileExtension);
            // Log File Full Path
            QString getLogFullPath();                                                           // myLogFullPath
            void setLogFullPath(const QString &thisLogFullPath);
            // File Foler Name
            QString getFileFolderName();                                                        // myFileFolderName
            void setFileFolderName(const QString &thisFileFolderName);
            // Module Name
            QString getModuleName();                                                            // myModuleName
            void setModuleName(const QString &thisModuleName);
            //
            QLoggerLevel::LogLevel getLogLevel();                                               // myLogLevel
            void setLogLevel(QLoggerLevel::LogLevel thisLogLevel);
            //
            void sendMessage(QLoggerLevel::LogLevel thisMsgType, const QString &thisModuleName, const QString &file, int line, const QString &function, const QString &msg);

        public slots:
            void onSettinChanged();

        signals:
            void handelSettinChanged(); //!< handelSettinChanged \brief Handel Settin Change.

        private:
            QSettings               *mySettings             = nullptr;                          //!< \c mySettings              \brief QSettings is used for this class.
            QString                 myLogPath               = "";                               //!< \c myLogPath               \brief Log Path: ${HOME}/AppName.
            QString                 myLogFolderName         = "";                               //!< \c myLogFolderName         \brief Log Folder Name: ${HOME}/AppName/LogFolderName.
            QString                 myLogFileName           = "";                               //!< \c myLogFileName           \brief Log File Name, if blank, make one up using pattern.
            QString                 myLogFullPath           = "";                               //!< \c myLogFullPath           \brief Log Full Path ${HOME}/AppName/LogFolderName/LogFileName.LogFileExtension.
            QString                 myLogNamePattern        = "";                               //!< \c myLogNamePattern        \brief Log Name Pattern: see Notes at top.
            QString                 myLogFileExtension      = "";                               //!< \c myLogFileExtension      \brief Log File Extension.
            QString                 myFilePath              = "";                               //!< \c myFilePath              \brief Path to the folder that holds the data, I named it data by default.
            QString                 myFileFolderName        = "";                               //!< \c myFileFolderName        \brief File Folder Name.
            QString                 myHomePath              = "";                               //!< \c myHomePath              \brief Home Path.
            QString                 myModuleName            = "";                               //!< \c myModuleName            \brief Module Name.
            QString                 myUserName              = "";                               //!< \c myUserName              \brief User Name.
            QString                 myPassword              = "";                               //!< \c myPassword             \brief User Name.
            QString                 myIniFileName           = "";                               //!< \c myIniFileName           \brief Ini File Name.
            QString                 myOrganizationName      = "";                               //!< \c myOrganizationName      \brief Organization Name.
            QString                 myOrganizationDomain    = "";                               //!< \c myOrganizationDomain    \brief Organization Domain.
            QString                 myApplicationName       = "";                               //!< \c myApplicationName       \brief Application Name.
            QString                 myUrl                   = "";                               //!< \c myUrl                   \brief URL used for HTTP request for Log Server.
            quint16                 myPort                  = 0;                                //!< \c myPort                  \brief Port Number of Log Server used URL.
            QLoggerManager         *myLoggerManager         = nullptr;                          //!< \c myLoggerManager         \brief QLogger Manager.
            QLoggerLevel::LogLevel  myLogLevel              = QLoggerLevel::LogLevel::Fatal;    //!< \c myLogLevel              \brief Maximum Log Level.
            bool                    isSet                   = false;                            //!< \c isSet                   \brief Track if mySettings has been set.

    }; // end class QLoggerCommon
} // end namespace QLogger
#endif // QLOGGERCOMMON_H
/* **************************   End of File ****************************   */
