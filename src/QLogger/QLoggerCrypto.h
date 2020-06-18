#pragma once
#ifndef QLOGGERCRYPTO_H
#define QLOGGERCRYPTO_H

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
#include "QLoggerCommon.h"

// Qt-AES
#include "QtAES/QAESEncryption.h"
namespace QLogger
{
    /******************************************************************************
    * class QLoggerCrypto                                                         *
    *******************************************************************************/
    class QLoggerCrypto : public QObject
    {
            Q_OBJECT
            Q_DISABLE_COPY(QLoggerCrypto)

        public:
            explicit QLoggerCrypto();
            ~QLoggerCrypto();
            // Enumerators
            /*!
                \enum PasswordCryptoMd
                \brief Password Crypto MD Hash.
             */
            enum PasswordCryptoMd
            {
                PasswordCryptoHashMd4,  //!< \c PasswordCryptoHashMd4 \brief Password Crypto Hash Md4 Minimal.
                PasswordCryptoHashMd5   //!< \c PasswordCryptoHashMd5 \brief Password Crypto Hash Md5 Highest.
            }; // end enum PasswordCryptoMdn
            /*!
                \enum PasswordCryptoSha
                \brief Password Crypto Sha Hash.
             */
            enum PasswordCryptoSha
            {
                PasswordCryptoHashSha1,      //!< \c PasswordCryptoHashSha1     \brief Password Crypto Hash Sha1 Minimal.
                PasswordCryptoHashSha224,    //!< \c PasswordCryptoHashSha224   \brief Password Crypto Hash Sha224 Medium Minimal.
                PasswordCryptoHashSha256,    //!< \c PasswordCryptoHashSha256   \brief Password Crypto Hash Sha256 Medium.
                PasswordCryptoHashSha384,    //!< \c PasswordCryptoHashSha384   \brief Password Crypto Hash Sha384 Medium High.
                PasswordCryptoHashSha512,    //!< \c PasswordCryptoHashSha512   \brief Password Crypto Hash Sha512 Highest.
                PasswordCryptoHashSha3_224,  //!< \c PasswordCryptoHashSha3_224 \brief Password Crypto Hash Sha3_224 Minimal.
                PasswordCryptoHashSha3_256,  //!< \c PasswordCryptoHashSha3_256 \brief Password Crypto Hash Sha3_256 Medium.
                PasswordCryptoHashSha3_384,  //!< \c PasswordCryptoHashSha3_384 \brief Password Crypto Hash Sha3_384 Medium High.
                PasswordCryptoHashSha3_512   //!< \c PasswordCryptoHashSha3_512 \brief Password Crypto Hash Sha3_512 Highest.
            }; // end enum PasswordCryptoSha
            /*!
                \enum PasswordCryptoKeccak
                \brief Password Crypto Keccak.
             */
            enum PasswordCryptoKeccak
            {
                PasswordCryptoHashKeccak_224,  //!< \c PasswordCryptoHashKeccak_224 \brief Password Crypto Hash Keccak_224 Minimal.
                PasswordCryptoHashKeccak_256,  //!< \c PasswordCryptoHashKeccak_256 \brief Password Crypto Hash Keccak_256 Medium.
                PasswordCryptoHashKeccak_384,  //!< \c PasswordCryptoHashKeccak_384 \brief Password Crypto Hash Keccak_384 Medium High.
                PasswordCryptoHashKeccak_512   //!< \c PasswordCryptoHashKeccak_512 \brief Password Crypto Hash Keccak_512 Highest.
            }; // end enum PasswordCryptoKeccak
            Q_ENUM(PasswordCryptoMd)       //!< \brief I use MD 4 or 5 as a Seed to AES.
            Q_ENUM(PasswordCryptoSha)      //!< \brief I use SHAx also as a Seed to AES.
            Q_ENUM(PasswordCryptoKeccak)   //!< \brief I use Keccakx for other things.
            //
            // No matter what function I put here, I will get a warning warning: documented symbol 'x' was not declared or defined.
            QString getCryptoKey();
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
            void handelSettingChanged(); //!< \brief handel Setting Change.

        private:
            QString                 myCryptoKey             = "";                               //!< \c myCryptoKey         \brief Argument to Constructor from main.cpp.
            QString                 myCryptoIvVector        = "";                               //!< \c myCryptoIvVector    \brief Argument to Constructor from main.cpp.
            PasswordCryptoMd        myCryptoMd              = PasswordCryptoHashMd5;            //!< \c myCryptoMd          \brief PasswordCryptoHashMd4, PasswordCryptoHashMd5.
            PasswordCryptoSha       myCryptoSha             = PasswordCryptoHashSha3_512;       //!< \c myCryptoSha         \brief PasswordCryptoHashSha1, PasswordCryptoHashSha224, PasswordCryptoHashSha256, PasswordCryptoHashSha384, PasswordCryptoHashSha512, PasswordCryptoHashSha3_224, PasswordCryptoHashSha3_256, PasswordCryptoHashSha3_384, PasswordCryptoHashSha3_512.
            PasswordCryptoKeccak    myCryptoKeccak          = PasswordCryptoHashKeccak_512;     //!< \c myCryptoKeccak      \brief PasswordCryptoHashKeccak_224, PasswordCryptoHashKeccak_256, PasswordCryptoHashKeccak_384, PasswordCryptoHashKeccak_512.
            QByteArray              myHashKey;                                                  //!< \c myHashKey           \brief used for Encryption and Decrytion.
            QByteArray              myHashIV;                                                   //!< \c myHashIV            \brief used for Encryption and Decrytion.
            QLoggerCommon          *qLoggerCommon           = nullptr;                          //!< \c qLoggerCommon       \brief Logger Common Instance.
    }; // end class QLoggerCrypto
} // end namespace QLogger
#endif // QLOGGERCRYPTO_H
/******************************* End of File *********************************/

