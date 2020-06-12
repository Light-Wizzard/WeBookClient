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

// QLogger Common
#include "QLogger/QLoggerCommon.h"

// Qt-AES
#include "QtAES/QAESEncryption.h"
/******************************************************************************
** class WeBookCrypto                                                         *
*******************************************************************************/
class WeBookCrypto : public QObject
{
        Q_OBJECT
        Q_DISABLE_COPY(WeBookCrypto)

    public:
        explicit WeBookCrypto();
        ~WeBookCrypto();
        //
        const QString constCryptoKey             = "!1@2#3$4%5^6&7*8)9(0)NowPickRand"; // These values are for testing only
        const QString constCryptoIvVector        = "PutMoveVector1!2@3#4$NowPickRand"; // These values are for testing only
        // Enumerators
        enum PasswordCryptoMd     { PasswordCryptoHashMd4, PasswordCryptoHashMd5 }; // Used for data encyption
        enum PasswordCryptoSha    { PasswordCryptoHashSha1, PasswordCryptoHashSha224, PasswordCryptoHashSha256, PasswordCryptoHashSha384, PasswordCryptoHashSha512, PasswordCryptoHashSha3_224, PasswordCryptoHashSha3_256, PasswordCryptoHashSha3_384, PasswordCryptoHashSha3_512 };
        enum PasswordCryptoKeccak { PasswordCryptoHashKeccak_224, PasswordCryptoHashKeccak_256, PasswordCryptoHashKeccak_384, PasswordCryptoHashKeccak_512 };
        Q_ENUM(PasswordCryptoMd)       // I use MD 4 or 5 as a Seed to AES
        Q_ENUM(PasswordCryptoSha)      // I use SHAx also as a Seed to AES
        Q_ENUM(PasswordCryptoKeccak)   // I am leaving this in, in case I want to use it

        // Crypto Key
        QString getCryptoKey();                                                             // myCryptoKey
        void setCryptoKey(const QString &thisCryptoKey);
        // Crypto IV Vector
        QString getCryptoIvVector();                                                        // myCryptoIvVector
        void setCryptoIvVector(const QString &thisCryptoIvVector);
        //
        QByteArray getHashKey();
        QByteArray getHashIV();
        // Crypto
        QString getMd();                                                                    // PasswordCryptoMd     myCryptoMd
        QString getSha();                                                                   // PasswordCryptoSha    myCryptoSha
        QString getKeccak(const QString &thisIvVector);                                     // PasswordCryptoKeccak myCryptoKeccak
        QString enCodeSecret(const QString &thisSecretString);                              // enCode Secret AES
        QString deCodeSecret(const QString &thisSecretString);                              // deCode Secret AES
        void setCryptoCodeHashish();                                                        // set Crypto Code Hashish (Hash Like: combines both cryptoKey and cryptoIvVector, to form AES Encrytion)

    signals:
        void handelSettinChanged();

    private:
        QString                 myCryptoKey             = "";                               // Argument to Constructor from main.cpp
        QString                 myCryptoIvVector        = "";                               // Argument to Constructor from main.cpp
        PasswordCryptoMd        myCryptoMd              = PasswordCryptoHashMd5;            // PasswordCryptoHashMd4, PasswordCryptoHashMd5
        PasswordCryptoSha       myCryptoSha             = PasswordCryptoHashSha3_512;       // PasswordCryptoHashSha1, PasswordCryptoHashSha224, PasswordCryptoHashSha256, PasswordCryptoHashSha384, PasswordCryptoHashSha512, PasswordCryptoHashSha3_224, PasswordCryptoHashSha3_256, PasswordCryptoHashSha3_384, PasswordCryptoHashSha3_512
        PasswordCryptoKeccak    myCryptoKeccak          = PasswordCryptoHashKeccak_512;     // PasswordCryptoHashKeccak_224, PasswordCryptoHashKeccak_256, PasswordCryptoHashKeccak_384, PasswordCryptoHashKeccak_512
        QByteArray              myHashKey;                                                  // used for Encryption and Decrytion
        QByteArray              myHashIV;                                                   // used for Encryption and Decrytion
}; // end class WeBookCrypto
#endif // WEBOOKCOMMON_H
/* ***************************** End of File ******************************* */
