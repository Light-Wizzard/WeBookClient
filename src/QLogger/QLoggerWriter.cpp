/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerWriter.h"

#include "QLoggerWrapper.h"

#ifndef LOGLEVEL_CLASS
namespace
{
}
#endif
/******************************************************************************
** QLogger                                                                    *
*******************************************************************************/
namespace QLogger
{
    /******************************************************************************
    ** QLoggerWriter Constructor                                                  *
    *******************************************************************************/
    // FIXME make logs a variable you can change
#ifdef LOGLEVEL_CLASS
    QLoggerWriter::QLoggerWriter(const QString &fileDestination, QLoggerLevel::LogLevel level) : QThread(), mFileDestination(fileDestination),  mLevel(level)
#else
    QLoggerWriter::QLoggerWriter(const QString &fileDestination, LogLevel level) : QThread(), mFileDestination(fileDestination),  mLevel(level)
#endif
    {
        //mFileDestination = "logs/" + fileDestination;
        //mLevel = level;
    } // end QLoggerWriter
    /******************************************************************************
    ** renameFileIfFull                                                           *
    *******************************************************************************/
    QString QLoggerWriter::renameFileIfFull()
    {
        QFile file(mFileDestination);

        // Rename file if it's full
        if (file.size() >= MaxFileSize)
        {
            const auto newName = QString("%1_%2.log").arg(mFileDestination.left(mFileDestination.lastIndexOf('.')), QDateTime::currentDateTime().toString("dd_MM_yy__hh_mm_ss"));

            const auto renamed = file.rename(mFileDestination, newName);

            return renamed ? newName : QString();
        }

        return QString();
    } // end renameFileIfFull
    /******************************************************************************
    ** write                                                                      *
    *******************************************************************************/
    void QLoggerWriter::write(const QPair<QString, QString> &message)
    {
        QFile file(mFileDestination);

        const auto prevFilename = renameFileIfFull();

        if (file.open(QIODevice::ReadWrite | QIODevice::Text | QIODevice::Append))
        {
            QTextStream out(&file);

            if (!prevFilename.isEmpty()) out << QString("%1 - Previous log %2\n").arg(message.first, prevFilename);

            out << message.second;

            file.close();
        }
    } // end write
    /******************************************************************************
    ** enqueue                                                                    *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    void QLoggerWriter::enqueue(const QDateTime &date, const QString &threadId, const QString &module, QLoggerLevel::LogLevel level, const QString &fileName, int line, const QString &message)
#else
    void QLoggerWriter::enqueue(const QDateTime &date, const QString &threadId, const QString &module, LogLevel level, const QString &fileName, int line, const QString &message)
#endif
    {
        QString fileLine;
#ifdef LOGLEVEL_CLASS
#else
#endif

#ifdef LOGLEVEL_CLASS
        if (!fileName.isEmpty() && line > 0 && mLevel <= QLoggerLevel::LogLevel::Debug) fileLine = QString(" {%1:%2}").arg(fileName, QString::number(line));
#else
        if (!fileName.isEmpty() && line > 0 && mLevel <= LogLevel::Debug) fileLine = QString(" {%1:%2}").arg(fileName, QString::number(line));
#endif

#ifdef LOGLEVEL_CLASS
        const auto text = QString("[%1] [%2] [%3] [%4]%5 %6 \n").arg(QLoggerLevel::levelToText(level), module, date.toString("dd-MM-yyyy hh:mm:ss.zzz"), threadId, fileLine, message);
#else
        const auto text = QString("[%1] [%2] [%3] [%4]%5 %6 \n").arg(levelToText(level), module, date.toString("dd-MM-yyyy hh:mm:ss.zzz"), threadId, fileLine, message);
#endif

        QMutexLocker locker(&mutex);
        messages.append({ threadId, text });

        mQueueNotEmpty.wakeOne();
    } // end enqueue
    /******************************************************************************
    ** run                                                                        *
    *******************************************************************************/
    void QLoggerWriter::run()
    {
        while (!mQuit)
        {
            decltype(messages) copy;
            {
                QMutexLocker locker(&mutex);
                std::swap(copy, messages);
            }

            for (const auto &msg : copy) write(msg);

            copy.clear();

            mutex.lock();
            mQueueNotEmpty.wait(&mutex);
            mutex.unlock();
        }
    } // end run
    /******************************************************************************
    ** closeDestination                                                           *
    *******************************************************************************/
    void QLoggerWriter::closeDestination()
    {
        mQuit = true;
        mQueueNotEmpty.wakeOne();
        wait();
    } // end closeDestination
} // end
/* ***************************** End of File ******************************* */
