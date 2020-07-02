#include "WeBookFtpClient.h"
/******************************************************************************
* \fn WeBookFtpClient::WeBookFtpClient()
*******************************************************************************/
WeBookFtpClient::WeBookFtpClient(QObject *parent): QObject(parent)
{
    weBookSettings = new WeBookSettings(this);
}
/******************************************************************************
* \fn WeBookFtpClient::~WeBookFtpClient()
*******************************************************************************/
WeBookFtpClient::~WeBookFtpClient()
{
    // FIXME
}
/******************************************************************************
* \fn void WeBookFtpClient::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
*******************************************************************************/
void WeBookFtpClient::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    qDebug() << "Uploaded" << bytesSent << "of" << bytesTotal;
    emit handelFtpProgress(bytesSent, bytesTotal);
}
/******************************************************************************
* \fn void WeBookFtpClient::uploadDone()
*******************************************************************************/
void WeBookFtpClient::uploadDone()
{
    // FIXME
    qDebug() << "Finished" << networkReply->error();
    fileHandle->deleteLater();
    networkReply->deleteLater();
    handelFtpDone();
}
/******************************************************************************
* \fn void WeBookFtpClient::upload(const QString &file)
*
*******************************************************************************/
void WeBookFtpClient::upload(const QString &file)
{
    if (!QFile(file).exists())
    {
        // FIXME
        return;
    }
    QFileInfo fi(file);
    QString thatFileName = fi.fileName();

    QString thatUrl = QString("ftp://%1:%2/%3").arg(weBookSettings->getUrl()).arg(weBookSettings->getPort()).arg(thatFileName);
    QUrl url(thatUrl); // "ftp://url:port/fileName"
    url.setUserName(weBookSettings->getUserName());
    url.setPassword(weBookSettings->getPassword());
    url.setScheme("ftp");

    fileHandle = new QFile(file, this);
    if (fileHandle->open(QIODevice::ReadOnly))
    {
        networkReply = networkAccessManager.put(QNetworkRequest(url), fileHandle);
        connect(networkReply, &QNetworkReply::uploadProgress, this, &WeBookFtpClient::uploadProgress);
        connect(networkReply, &QNetworkReply::finished,       this, &WeBookFtpClient::uploadDone);
    }
    else
        qDebug() << "Oops";
}
/******************************* End of File *********************************/
