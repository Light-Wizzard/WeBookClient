#ifndef QLOGGERCOMMON_H
#define QLOGGERCOMMON_H

#include <QApplication>
#include <QtCore>
// QLogger Constants
#include "QLoggerConstants.h"
// QLogger Wrapper
#include "QLoggerWrapper.h"

/******************************************************************************
** namespace QLogger                                                          *
*******************************************************************************/
namespace QLogger
{
    /******************************************************************************
    ** class QLoggerCommon                                                        *
    *******************************************************************************/
    class QLoggerCommon : public QObject
    {
            Q_OBJECT
            Q_DISABLE_COPY(QLoggerCommon)

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
            QString getUserName();                                                               // myUserName
            void setUserName(const QString &thisUserName);
            // QSetter
            void qSettingsInstance();                                                                // QSetter
            bool     isSetting(const QString &thisFieldName);                                   // isSetting
            void     setSetting(const QString &thisKey, const QVariant &defaultValue);          // setSetting
            QVariant getSetting(const QString &key, const QVariant &defaultValue = QVariant()); // getSetting
            // Port of WeBookServer
            quint16 getPort();                                                                  // myPort
            QString portToString();
            void setPort(quint16 thisPort);
            // Logger
            void setWeBookLogger();
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
            QSettings               *mySettings             = nullptr;                          // QSettings is used for this class
            QString                 myLogPath               = "";                               // Log Path
            QString                 myLogFolderName         = "";                               // Log Folder Name
            QString                 myFilePath              = "";                               // Path to the folder that holds the data, I named it data by default
            QString                 myFileFolderName        = "";                               // File Folder Name
            QString                 myHomePath              = "";                               // Home Path
            QString                 myUserName              = "";                               // User Name
            QString                 myIniFileName           = "";                               // Ini File Name
            QString                 myOrganizationName      = "";                               // OrganizationName
            QString                 myOrganizationDomain    = "";                               // OrganizationDomain
            QString                 myApplicationName       = "";                               // ApplicationName
            QString                 myUrl                   = "";                               // URL used for HTTP request
            quint16                 myPort                  = 0;                                // Port Number used URL
            QLoggerManager         *manager                 = nullptr;                          // QLogger Manager

    }; // end class QLoggerCommon
} // end namespace QLogger
#endif // QLOGGERCOMMON_H
/* ***************************** End of File ******************************* */
