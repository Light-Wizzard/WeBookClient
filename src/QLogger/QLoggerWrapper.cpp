/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerWrapper.h"

namespace QLogger
{
    /******************************************************************************
    ** QLoggerWrapper Constructor                                                 *
    *******************************************************************************/
    QLoggerWrapper::QLoggerWrapper(const QString &thisModule, const QString &thisLogPath, QLoggerLevel::LogLevel level, const char *file, int line, const char *function) : myModule(thisModule), myLogPath(thisLogPath), myLogLevel(level), myFile(file), myLine(line), myFunction(function)
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
        QString thisMessage = QString("%1 (%2:%3 =>%4)").arg(myMessage).arg(myFile).arg(myLine).arg(myFunction);
        if (false)
        {
            // FIXME both are empty for some reason
            qDebug() << "QLoggerWrapper::~QLoggerWrapper() myModule=" << myModule << " myLogPath=" << myLogPath << " myMessage=" << myMessage << " myLogLevel=" << QLoggerLevel::levelToText(myLogLevel) << " myFile=" << myFile << " myLine=" << myLine << " myFunction=" << myFunction;
            QLOG_DEBUG() << thisMessage;
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
