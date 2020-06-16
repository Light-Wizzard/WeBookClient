/**************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
***************************************************************************/
#include "QLoggerCrypto.h"
namespace QLogger
{
    /**************************************************************************
    ** QLoggerCrypto Constructor                                              *
    ** Requires Setting:
    ** OrganizationName
    ** OrganizationDomain
    ** ApplicationName
    ***************************************************************************/
    QLoggerCrypto::QLoggerCrypto() : QObject()
    {
        qLoggerCommon = new QLoggerCommon(true);
    } // end QLoggerCrypto
    /**************************************************************************
    ** QLoggerCrypto Deconstructor                                            *
    ***************************************************************************/
    QLoggerCrypto::~QLoggerCrypto()
    {

    } // end ~QLoggerCrypto
    /**************************************************************************
    ** enCodeSecret(const QString &mySecretString)                            *
    ***************************************************************************/
    QString QLoggerCrypto::enCodeSecret(const QString &thisSecretString)
    {
        setCryptoCodeHashish();
        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        // FIXME Var for Debugging only
        QByteArray encodeText = encryption.encode(thisSecretString.toLocal8Bit(), getHashKey(), getHashKey());
        return encodeText;
    } // end enCodeSecret
    /**************************************************************************
    ** deCodeSecret(const QString &mySecretString)                            *
    ***************************************************************************/
    QString QLoggerCrypto::deCodeSecret(const QString &thisSecretString)
    {
        setCryptoCodeHashish();
        QAESEncryption encryption(QAESEncryption::AES_256, QAESEncryption::CBC);
        // FIXME Var for Debugging only
        QByteArray decodeText = encryption.decode(thisSecretString.toUtf8(), getHashKey(), getHashKey());
        QString decodedString = QString(encryption.removePadding(decodeText));
        return decodedString;
    } // end deCodeSecret
    /**************************************************************************
    ** setCryptoCodeHashish                                                   *
    ***************************************************************************/
    void QLoggerCrypto::setCryptoCodeHashish()
    {
        getSha();
        getSha();
    } // end setCryptoCodeHashish
    /**************************************************************************
    ** getCryptoKey                                                           *
    ***************************************************************************/
    QString QLoggerCrypto::getCryptoKey()
    {
        myCryptoKey = ConstDefaultCryptoKey;
        return myCryptoKey;
    } // end getCryptoKey
    /**************************************************************************
    ** setCryptoKey(QString myCrypokey)                                       *
    ***************************************************************************/
    void QLoggerCrypto::setCryptoKey(const QString &thisCryptoKey)
    {
        if (myCryptoKey.isEmpty() || myCryptoKey != thisCryptoKey)
        {
            myCryptoKey = thisCryptoKey;
            emit handelSettinChanged();
        }
    } // end setCryptoKey
    /**************************************************************************
    ** getCryptoIvVector                                                      *
    ***************************************************************************/
    QString QLoggerCrypto::getCryptoIvVector()
    {
        myCryptoIvVector = ConstDefaultCryptoIvVector;
        return myCryptoIvVector;
    } // end getCryptoIvVector
    /**************************************************************************
    ** setCryptoIvVector(QString myCrypokey)                                  *
    ***************************************************************************/
    void QLoggerCrypto::setCryptoIvVector(const QString &thisCryptoIvVector)
    {
        if (myCryptoIvVector.isEmpty() || myCryptoIvVector != thisCryptoIvVector)
        {
            myCryptoIvVector = thisCryptoIvVector;
            emit handelSettinChanged();
        }
    } // end setCryptoIvVector
    /**************************************************************************
    ** getHashKey                                                             *
    ***************************************************************************/
    QByteArray QLoggerCrypto::getHashKey()
    {
        if (myHashKey.isEmpty()) getSha();
        return myHashKey;
    } // end getHashKey
    /**************************************************************************
    ** getHashIV                                                              *
    ***************************************************************************/
    QByteArray QLoggerCrypto::getHashIV()
    {
        if (myHashIV.isEmpty()) getMd();
        return myHashIV;
    } // end getHashIV
    /**************************************************************************
    ** getKeccak                                                              *
    ***************************************************************************/
    QString QLoggerCrypto::getKeccak(const QString &thisIvVector)
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
    /**************************************************************************
    ** getMd                                                                  *
    ** Constant
    QCryptographicHash::Md4
    QCryptographicHash::Md5
    ***************************************************************************/
    QString QLoggerCrypto::getMd()
    {
        QString securePassword;
        switch (myCryptoMd)
        {
            case PasswordCryptoHashMd4:
                securePassword = QString(QCryptographicHash::hash((getCryptoKey().toUtf8()), QCryptographicHash::Md4).toHex());
                myHashIV       = QCryptographicHash::hash(getCryptoIvVector().toLocal8Bit(), QCryptographicHash::Md4);
                break;
            case PasswordCryptoHashMd5:
                securePassword = QString(QCryptographicHash::hash((getCryptoKey().toUtf8()), QCryptographicHash::Md5).toHex());
                myHashIV       = QCryptographicHash::hash(getCryptoIvVector().toLocal8Bit(), QCryptographicHash::Md5);
                break;
        }
        return securePassword;
    } // end getMd
    /**************************************************************************
    ** getSha                                                                 *
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
    ***************************************************************************/
    QString QLoggerCrypto::getSha()
    {
        QString securePassword;
        switch (myCryptoSha)
        {
            case PasswordCryptoHashSha1:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha1).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha1);
                break;
            case PasswordCryptoHashSha224:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha224).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha224);
                break;
            case PasswordCryptoHashSha256:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha256).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha256);
                break;
            case PasswordCryptoHashSha384:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha384).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha384);
                break;
            case PasswordCryptoHashSha512:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha512).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha512);
                break;
            case PasswordCryptoHashSha3_224:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha3_224).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha3_224);
                break;
            case PasswordCryptoHashSha3_256:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha3_256).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha3_256);
                break;
            case PasswordCryptoHashSha3_384:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha3_384).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha3_384);
                break;
            case PasswordCryptoHashSha3_512:
                securePassword = QString(QCryptographicHash::hash((getCryptoIvVector().toUtf8()), QCryptographicHash::Sha3_512).toHex());
                myHashKey      = QCryptographicHash::hash(getCryptoKey().toLocal8Bit(),           QCryptographicHash::Sha3_512);
                break;
        }
        return securePassword;
    } // end getSha
} // end namespace QLogger
/* ***************************** End of File ******************************* */
