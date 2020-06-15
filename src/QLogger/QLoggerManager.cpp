/******************************************************************************
** QLogger                                                                    *
** Thread-safe logger for Qt applications                                     *
** https://github.com/francescmm/QLogger                                      *
** Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerManager.h"

#ifdef LOGLEVEL_CLASS
Q_DECLARE_METATYPE(QLogger::QLoggerLevel::LogLevel);
#else
Q_DECLARE_METATYPE(QLogger::LogLevel);
#endif
/******************************************************************************
** QLogger                                                                    *
*******************************************************************************/
namespace QLogger
{
    /******************************************************************************
    ** QLog_                                                                      *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    void QLog_(const QString &module, QLoggerLevel::LogLevel level, const QString &message, const QString &file, int line)
#else
    void QLog_(const QString &module, LogLevel level, const QString &message, const QString &file, int line)
#endif
    {
        QLoggerManager::getInstance()->enqueueMessage(module, level, message, file, line);
    }
    /******************************************************************************
    ** QUEUE_LIMIT                                                                *
    *******************************************************************************/
    static const int QUEUE_LIMIT = 100;
    /******************************************************************************
    ** QLoggerManager Constructor                                                 *
    *******************************************************************************/
    QLoggerManager::QLoggerManager() : mMutex(QMutex::Recursive)
    {
        QDir dir(QDir::currentPath());
        dir.mkdir("logs");
    }
    /******************************************************************************
    ** getInstance                                                                *
    *******************************************************************************/
    QLoggerManager *QLoggerManager::getInstance()
    {
        static QLoggerManager INSTANCE;

        return &INSTANCE;
    } // end getInstance
    /******************************************************************************
    ** addDestination                                                             *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    bool QLoggerManager::addDestination(const QString &fileDest, const QString &module, QLoggerLevel::LogLevel level)
#else
    bool QLoggerManager::addDestination(const QString &fileDest, const QString &module, LogLevel level)
#endif
    {
        QMutexLocker lock(&mMutex);

        if (!mModuleDest.contains(module))
        {
            const auto log = new QLoggerWriter(fileDest, level);
            log->stop(mIsStop);

            const auto threadId = QString("%1").arg((quintptr)QThread::currentThread(), QT_POINTER_SIZE * 2, 16, QChar('0'));

#ifdef LOGLEVEL_CLASS
            log->enqueue(QDateTime::currentDateTime(), threadId, module, QLoggerLevel::LogLevel::Info, "", -1, "Adding destination!");
#else
            log->enqueue(QDateTime::currentDateTime(), threadId, module, LogLevel::Info, "", -1, "Adding destination!");
#endif

            mModuleDest.insert(module, log);

            log->start();

            return true;
        }

        return false;
    }
    /******************************************************************************
    ** addDestination                                                             *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    bool QLoggerManager::addDestination(const QString &fileDest, const QStringList &modules, QLoggerLevel::LogLevel level)
#else
    bool QLoggerManager::addDestination(const QString &fileDest, const QStringList &modules, LogLevel level)
#endif
    {
        QMutexLocker lock(&mMutex);
        bool allAdded = false;

        for (const auto &module : modules)
        {
            if (!mModuleDest.contains(module))
            {
                const auto log = new QLoggerWriter(fileDest, level);
                log->stop(mIsStop);

                const auto threadId = QString("%1").arg((quintptr)QThread::currentThread(), QT_POINTER_SIZE * 2, 16, QChar('0'));

#ifdef LOGLEVEL_CLASS
                log->enqueue(QDateTime::currentDateTime(), threadId, module, QLoggerLevel::LogLevel::Info, "", -1, "Adding destination!");
#else
                log->enqueue(QDateTime::currentDateTime(), threadId, module, LogLevel::Info, "", -1, "Adding destination!");
#endif

                mModuleDest.insert(module, log);

                log->start();

                allAdded = true;
            }
        }

        return allAdded;
    }
    /******************************************************************************
    ** writeAndDequeueMessages                                                    *
    *******************************************************************************/
    void QLoggerManager::writeAndDequeueMessages(const QString &module)
    {
        QMutexLocker lock(&mMutex);

        const auto logWriter = mModuleDest.value(module);

        if (logWriter && !logWriter->isStop())
        {
            for (const auto &values : mNonWriterQueue)
            {
#ifdef LOGLEVEL_CLASS
                // .toInt() crashes
                //const auto level = qvariant_cast<QLoggerLevel::LogLevel>(values.at(2).toInt());
                const auto level = qvariant_cast<QLoggerLevel::LogLevel>(values.at(2));
#else

                //const auto level = static_cast<LogLevel>(values.at(2).toInt());
                const auto level = qvariant_cast<LogLevel>(values.at(2));

                //const auto level = qvariant_cast<LogLevel>(values.at(2).toInt());
#endif

                if (logWriter->getLevel() <= level)
                {
                    const auto datetime = values.at(0).toDateTime();
                    const auto threadId = values.at(1).toString();
                    const auto file = values.at(3).toString();
                    const auto line = values.at(4).toInt();
                    const auto message = values.at(5).toString();

                    logWriter->enqueue(datetime, threadId, module, level, file, line, message);
                }
            }

            mNonWriterQueue.remove(module);
        }
    }
    /******************************************************************************
    ** enqueueMessage                                                             *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    void QLoggerManager::enqueueMessage(const QString &module, QLoggerLevel::LogLevel level, const QString &message, QString file, int line)
#else
    void QLoggerManager::enqueueMessage(const QString &module, LogLevel level, const QString &message, QString file, int line)
#endif
    {
        QMutexLocker lock(&mMutex);
        const auto threadId = QString("%1").arg((quintptr)QThread::currentThread(), QT_POINTER_SIZE * 2, 16, QChar('0'));
        const auto fileName = file.mid(file.lastIndexOf('/') + 1);
        const auto logWriter = mModuleDest.value(module);

        if (logWriter && !logWriter->isStop() && logWriter->getLevel() <= level)
        {
            writeAndDequeueMessages(module);

            logWriter->enqueue(QDateTime::currentDateTime(), threadId, module, level, fileName, line, message);
        }
        else if (!logWriter && mNonWriterQueue.count(module) < QUEUE_LIMIT)
        {
#ifdef LOGLEVEL_CLASS
            mNonWriterQueue.insert( module, { QDateTime::currentDateTime(), threadId, QVariant::fromValue<QLoggerLevel::LogLevel>(level), fileName, line, message });
#else
            mNonWriterQueue.insert( module, { QDateTime::currentDateTime(), threadId, QVariant::fromValue<LogLevel>(level), fileName, line, message });
#endif
        }
    } // end enqueueMessage
    /******************************************************************************
    ** pause                                                                      *
    *******************************************************************************/
    void QLoggerManager::pause()
    {
        QMutexLocker lock(&mMutex);

        mIsStop = true;

        for (auto &logWriter : mModuleDest) logWriter->stop(mIsStop);
    } // end pause
    /******************************************************************************
    ** resume                                                                     *
    *******************************************************************************/
    void QLoggerManager::resume()
    {
        QMutexLocker lock(&mMutex);

        mIsStop = false;

        for (auto &logWriter : mModuleDest) logWriter->stop(mIsStop);
    } // end resume
    /******************************************************************************
    ** overwriteLogLevel                                                          *
    *******************************************************************************/
#ifdef LOGLEVEL_CLASS
    void QLoggerManager::overwriteLogLevel(QLoggerLevel::LogLevel level)
#else
    void QLoggerManager::overwriteLogLevel(LogLevel level)
#endif
    {
        QMutexLocker lock(&mMutex);

        for (auto &logWriter : mModuleDest) logWriter->setLogLevel(level);
    }
    /******************************************************************************
    ** QLoggerManager Deconstructor                                               *
    *******************************************************************************/
    QLoggerManager::~QLoggerManager()
    {
        QMutexLocker locker(&mMutex);

        for (const auto &dest : mModuleDest.toStdMap())
            writeAndDequeueMessages(dest.first);

        for (auto dest : mModuleDest)
        {
            dest->closeDestination();
            delete dest;
        }

        mModuleDest.clear();
    } // end ~QLoggerManager
} // end namespace QLogger
/* ***************************** End of File ******************************* */
