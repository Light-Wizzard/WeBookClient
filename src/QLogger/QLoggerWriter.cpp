/**************************************************************************
* QLogger                                                                    *
* Thread-safe logger for Qt applications                                     *
* https://github.com/francescmm/QLogger                                      *
* Fork: https://github.com/Light-Wizzard/QLogger                             *
***************************************************************************/
#include "QLoggerWriter.h"
/**************************************************************************
* QLogger                                                                 *
***************************************************************************/
namespace QLogger
{
    /**************************************************************************
    * QLoggerWriter Constructor                                               *
    ***************************************************************************/
    /*!
       \class QLoggerWriter
       \fn QLoggerWriter::QLoggerWriter(const QString &fileDestination, QLoggerLevel::LogLevel level) : QThread(), mFileDestination(fileDestination),  mLevel(level)
       \brief Logger Writer.
     */
    QLoggerWriter::QLoggerWriter(const QString &fileDestination, QLoggerLevel::LogLevel level) : QThread(), mFileDestination(fileDestination),  mLevel(level)
    {
        // Pass in full path
        //mFileDestination = "logs/" + fileDestination;
        //mLevel = level;
    } // end QLoggerWriter
    /**************************************************************************
    * renameFileIfFull                                                        *
    ***************************************************************************/
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
    /**************************************************************************
    * write                                                                   *
    ***************************************************************************/
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
    /**************************************************************************
    * enqueue                                                                 *
    ***************************************************************************/
    void QLoggerWriter::enqueue(const QDateTime &date, const QString &threadId, const QString &module, QLoggerLevel::LogLevel level, const QString &fileName, int line, const QString &theFunction, const QString &message)
    {
        QString fileLine;
        //  && mLevel <= QLoggerLevel::LogLevel::Debug
        if (!fileName.isEmpty() && !theFunction.isEmpty() && line > 0) fileLine = QString(" {%1:%2=>%3}").arg(fileName, QString::number(line), theFunction);

        const auto text = QString("[%1] [%2] [%3]%4 %5 \n").arg(QLoggerLevel::levelToText(level), module, date.toString("dd-MM-yyyy hh:mm:ss.zzz"), fileLine, message);

        QMutexLocker locker(&mutex);
        messages.append({ threadId, text });

        mQueueNotEmpty.wakeOne();
    } // end enqueue
    /**************************************************************************
    * run                                                                     *
    ***************************************************************************/
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
    /**************************************************************************
    * closeDestination                                                        *
    * FIXME Hanges on quiting app
    ***************************************************************************/
    void QLoggerWriter::closeDestination()
    {
        mQuit = true;
        mQueueNotEmpty.wakeOne();
        exit(1); // exit(0) causes fatal error
        //wait(); // wait or exit does not matter, still hangs on exit
    } // end closeDestination
} // end closeDestination
/******************************* End of File *********************************/

