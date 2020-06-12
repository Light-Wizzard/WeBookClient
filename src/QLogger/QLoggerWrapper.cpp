/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerWrapper.h"

namespace QLogger
{
    void QLogIt(const QString &module, QLoggerLevel::LogLevel level, const QString &message, const QString &file, int line)
    {
        QLoggerManager::getInstance()->enqueueMessage(module, level, message, file, line);
    }
    /******************************************************************************
    ** QLoggerWrapper Constructor                                                 *
    *******************************************************************************/
    QLoggerWrapper::QLoggerWrapper(QLoggerLevel::LogLevel level, const char *file, int line, const char *function) : myLogLevel(level), myFile(file), myLine(line), myFunction(function)
    {
        // init
    } // end CuteMessageLogger
    /******************************************************************************
    ** ~CuteMessageLogger Deconstructor                                           *
    ** manager = QLogger::QLoggerManager::getInstance();
    ** manager->addDestination(QLogger::myLogFile, QLogger::myModule, QLogger::LogLevel::Debug);
    *******************************************************************************/
    QLoggerWrapper::~QLoggerWrapper()
    {
        //QLoggerCommon *qLoggerCommon = new QLoggerCommon(true);  Q_UNUSED(qLoggerCommon)
        QString thisMessage = QString("%1 (%2:%3 =>%4)").arg(myMessage, myFile, QString::number(myLine), myFunction);
        qDebug() << thisMessage;
        // FIXME this crashes in deconstructor, calling it from one, cannot imagine the lifetime issue
        //QLoggerManager::getInstance()->enqueueMessage(myMessage, myLogLevel, myMessage, myFile, myLine);
        // void QLog_(const QString &module, QLogger::QLoggerLevel::LogLevel level, const QString &message, const QString &file = QString(), int line = -1);
        //QLogIt(myModule, myLogLevel, myMessage, QString(myFile), myLine);
        if (false)
        {
            qDebug() << "QLoggerWrapper::~QLoggerWrapper() myModule=" << myModule << " myLogPath=" << myLogPath << " myMessage=" << myMessage << " myLogLevel=" << QLoggerLevel::levelToText(myLogLevel) << " myFile=" << myFile << " myLine=" << myLine << " myFunction=" << myFunction;
        }
    } // end ~QLoggerWrapper
    /******************************************************************************
    ** write                                                                      *
    *******************************************************************************/
    void QLoggerWrapper::write(const char *msg, ...)
    {
        va_list va;
        va_start(va, msg);
        myMessage = QString::vasprintf(msg, va);
        va_end(va);
    } // end write
    /******************************************************************************
    ** write                                                                      *
    *******************************************************************************/
    void QLoggerWrapper::write(const QString &msg)
    {
        myMessage = msg;
    } // end write
    /******************************************************************************
    ** write                                                                      *
    *******************************************************************************/
    QDebug QLoggerWrapper::write()
    {
        QDebug d(&myMessage);
        return d;
    } // end write
} // end namespace QLogger
/* ***************************** End of File ******************************* */