/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/
#include "QLoggerWrapper.h"
#ifndef LOGLEVEL_CLASS
namespace
{
    QString levelToText(const QLogger::LogLevel &level)
    {
        switch (level)
        {
            case QLogger::LogLevel::Trace:
                return "Trace";
            case QLogger::LogLevel::Debug:
                return "Debug";
            case QLogger::LogLevel::Info:
                return "Info";
            case QLogger::LogLevel::Warning:
                return "Warning";
            case QLogger::LogLevel::Error:
                return "Error";
            case QLogger::LogLevel::Fatal:
                return "Fatal";
        }

        return QString();
    }
}
#endif

namespace QLogger
{
#ifdef LOGLEVEL_CLASS
    void QLogIt(const QString &module, QLoggerLevel::LogLevel level, const QString &message, const QString &file, int line)
#else
    void QLogIt(const QString &module, LogLevel level, const QString &message, const QString &file, int line)
#endif
    {
        QLoggerManager::getInstance()->enqueueMessage(module, level, message, file, line);
    }
    /******************************************************************************
    ** QLoggerWrapper Constructor                                                 *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    QLoggerWrapper::QLoggerWrapper(QLoggerLevel::LogLevel level, const char *file, int line, const char *function) : myLogLevel(level), myFile(file), myLine(line), myFunction(function)
#else
    QLoggerWrapper::QLoggerWrapper(LogLevel level, const char *file, int line, const char *function) : myLogLevel(level), myFile(file), myLine(line), myFunction(function)
#endif
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
#ifdef LOGLEVEL_CLASS
        //QLoggerManager::getInstance()->enqueueMessage(myMessage, myLogLevel, myMessage, myFile, myLine);
        QLoggerManager::getInstance()->enqueueMessage(myMessage, QLoggerLevel::LogLevel::Trace, myMessage, myFile, myLine);
        //QLogIt(myModule, myLogLevel, myMessage, QString(myFile), myLine);
#else
        // Any of these methods crash
        //QLoggerManager::getInstance()->enqueueMessage(myMessage, myLogLevel, myMessage, myFile, myLine);
        //QLoggerManager::getInstance()->enqueueMessage(myMessage, LogLevel::Trace, myMessage, myFile, myLine);
        //QLogIt(myModule, myLogLevel, myMessage, QString(myFile), myLine);
#endif
        // void QLog_(const QString &module, QLogger::QLoggerLevel::LogLevel level, const QString &message, const QString &file = QString(), int line = -1);
        if (false)
        {
#ifdef LOGLEVEL_CLASS
            qDebug() << "QLoggerWrapper::~QLoggerWrapper() myModule=" << myModule << " myLogPath=" << myLogPath << " myMessage=" << myMessage << " myLogLevel=" << QLoggerLevel::levelToText(myLogLevel) << " myFile=" << myFile << " myLine=" << myLine << " myFunction=" << myFunction;
#else
            qDebug() << "QLoggerWrapper::~QLoggerWrapper() myModule=" << myModule << " myLogPath=" << myLogPath << " myMessage=" << myMessage << " myLogLevel=" << levelToText(myLogLevel) << " myFile=" << myFile << " myLine=" << myLine << " myFunction=" << myFunction;
#endif
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
