/******************************************************************************
* QLogger                                                                    *
* Thread-safe logger for Qt applications                                     *
* https://github.com/francescmm/QLogger                                      *
* Fork: https://github.com/Light-Wizzard/QLogger                             *
*******************************************************************************/

#include "QLoggerManager.h"

Q_DECLARE_METATYPE(QLoggerLevel::LogLevel);
/******************************************************************************
* QLogger                                                                    *
*******************************************************************************/
namespace QLogger
{
    /*!
       \class QLoggerManager
       \brief Logger Manager.
     */
    /**************************************************************************
    * QLog_                                                                  *
    ***************************************************************************/
    void QLog_(const QString &module, QLoggerLevel::LogLevel level, const QString &message, const QString &file, int line, const QString &theFunction)
    {
        QLoggerManager::getInstance()->enqueueMessage(module, level, message, file, line, theFunction);
    }
    /**************************************************************************
    * QUEUE_LIMIT                                                            *
    ***************************************************************************/
    static const int QUEUE_LIMIT = 100;
    /**************************************************************************
    * QLoggerManager Constructor                                             *
    * FIXME logs
    ***************************************************************************/
    QLoggerManager::QLoggerManager() : mMutex(QMutex::Recursive)
    {
        //QDir dir(QDir::currentPath());
        //dir.mkdir("logs");
    }
    /**************************************************************************
    * QLoggerManager Deconstructor                                           *
    ***************************************************************************/
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
    /**************************************************************************
    * getInstance                                                            *
    ***************************************************************************/
    QLoggerManager *QLoggerManager::getInstance()
    {
        static QLoggerManager INSTANCE;

        return &INSTANCE;
    } // end getInstance
    /**************************************************************************
    * addDestination                                                         *
    * FIXME Translate
    ***************************************************************************/
    bool QLoggerManager::addDestination(const QString &fileDest, const QString &module, QLoggerLevel::LogLevel level)
    {
        QMutexLocker lock(&mMutex);

        if (!mModuleDest.contains(module))
        {
            const auto log = new QLoggerWriter(fileDest, level);
            log->stop(mIsStop);

            const auto threadId = QString("%1").arg((quintptr)QThread::currentThread(), QT_POINTER_SIZE * 2, 16, QChar('0'));

            log->enqueue(QDateTime::currentDateTime(), threadId, module, QLoggerLevel::LogLevel::Info, QLOGGER_MESSAGELOG_FILE, QLOGGER_MESSAGELOG_LINE, QLOGGER_MESSAGELOG_FUNC, "Adding destination!");

            mModuleDest.insert(module, log);

            log->start();

            return true;
        }

        return false;
    }
    /**************************************************************************
    * addDestination                                                         *
    ***************************************************************************/
    bool QLoggerManager::addDestination(const QString &fileDest, const QStringList &modules, QLoggerLevel::LogLevel level)
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

                log->enqueue(QDateTime::currentDateTime(), threadId, module, QLoggerLevel::LogLevel::Info, "", -1, Q_FUNC_INFO, "Adding destination!");

                mModuleDest.insert(module, log);

                log->start();

                allAdded = true;
            }
        }

        return allAdded;
    }
    /**************************************************************************
    * writeAndDequeueMessages                                                *
    ***************************************************************************/
    void QLoggerManager::writeAndDequeueMessages(const QString &module)
    {
        QMutexLocker lock(&mMutex);

        const auto logWriter = mModuleDest.value(module);

        if (logWriter && !logWriter->isStop())
        {
            for (const auto &values : mNonWriterQueue)
            {
                // .toInt() crashes
                //const auto level = qvariant_cast<QLoggerLevel::LogLevel>(values.at(2).toInt());
                const auto level = qvariant_cast<QLoggerLevel::LogLevel>(values.at(2));

                //if (logWriter->getLevel() <= level) {
                    const auto datetime = values.at(0).toDateTime();
                    const auto threadId = values.at(1).toString();
                    const auto file = values.at(3).toString();
                    const auto line = values.at(4).toInt();
                    const auto theFunction = values.at(5).toString();
                    const auto message = values.at(6).toString();

                    logWriter->enqueue(datetime, threadId, module, level, file, line, theFunction, message);
               // }
            }

            mNonWriterQueue.remove(module);
        }
    }
    /**************************************************************************
    * enqueueMessage                                                         *
    ***************************************************************************/
    void QLoggerManager::enqueueMessage(const QString &module, QLoggerLevel::LogLevel level, const QString &message, QString file, int line, const QString &theFunction)
    {
        QMutexLocker lock(&mMutex);
        const auto threadId = QString("%1").arg((quintptr)QThread::currentThread(), QT_POINTER_SIZE * 2, 16, QChar('0'));
        const auto fileName = file.mid(file.lastIndexOf('/') + 1);
        const auto logWriter = mModuleDest.value(module);

        if (logWriter && !logWriter->isStop()) //  && logWriter->getLevel() <= level
        {
            writeAndDequeueMessages(module);

            logWriter->enqueue(QDateTime::currentDateTime(), threadId, module, level, fileName, line, theFunction, message);
        }
        else if (!logWriter && mNonWriterQueue.count(module) < QUEUE_LIMIT)
        {
            mNonWriterQueue.insert( module, { QDateTime::currentDateTime(), threadId, QVariant::fromValue<QLoggerLevel::LogLevel>(level), fileName, line, theFunction, message });
        }
    } // end enqueueMessage
    /**************************************************************************
    * pause                                                                  *
    ***************************************************************************/
    void QLoggerManager::pause()
    {
        QMutexLocker lock(&mMutex);

        mIsStop = true;

        for (auto &logWriter : mModuleDest) logWriter->stop(mIsStop);
    } // end pause
    /**************************************************************************
    * resume                                                                 *
    ***************************************************************************/
    void QLoggerManager::resume()
    {
        QMutexLocker lock(&mMutex);

        mIsStop = false;

        for (auto &logWriter : mModuleDest) logWriter->stop(mIsStop);
    } // end resume
    /**************************************************************************
    * overwriteLogLevel                                                      *
    ***************************************************************************/
    void QLoggerManager::overwriteLogLevel(QLoggerLevel::LogLevel level)
    {
        QMutexLocker lock(&mMutex);

        for (auto &logWriter : mModuleDest) logWriter->setLogLevel(level);
    }
} // end namespace QLogger
/******************************* End of File *********************************/

