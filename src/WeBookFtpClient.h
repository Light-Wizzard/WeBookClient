#ifndef WEBOOKFTPCLIENT_H
#define WEBOOKFTPCLIENT_H

#include <QObject>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include "WeBookSettings.h"
#include "WeBookCrypto.h"
/******************************************************************************
* class WeBookFtpClient : public QObject                                      *
*******************************************************************************/
class WeBookFtpClient : public QObject
{
        Q_OBJECT
    public:
        WeBookFtpClient(QObject *parent = nullptr);
        ~WeBookFtpClient();

        void upload(const QString &file);

    signals:
        void handelFtpProgress(qint64 bytesSent, qint64 bytesTotal); //!< onFtpProgress
        void handelFtpDone();                                        //!< onFtpDone

    public slots:
        void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
        void uploadDone();

    private:
        QNetworkAccessManager networkAccessManager;
        QFile *fileHandle;
        QNetworkReply   *networkReply;
        WeBookSettings  *weBookSettings      = nullptr;   //!< Logging and QtSettings
        WeBookCrypto    *weBookCrypto        = nullptr;   //!< Crypto

}; // end class WeBookFtpClient
#endif // WEBOOKFTPCLIENT_H
/******************************* End of File *********************************/
