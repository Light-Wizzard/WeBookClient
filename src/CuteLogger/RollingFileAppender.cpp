#include <QDateTime>
#include <QDir>
#include <QFileInfo>

#include "RollingFileAppender.h"

/******************************************************************************
** RollingFileAppender Constructor                                            *
*******************************************************************************/
RollingFileAppender::RollingFileAppender(const QString &fileName) : FileAppender(fileName), myFrequency(DailyRollover), myLogFilesLimit(0)
{

} // end RollingFileAppender
/******************************************************************************
** append                                                                     *
*******************************************************************************/
void RollingFileAppender::append(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line, const char *function, const QString &category, const QString &message)
{
    if (!myRollOverTime.isNull() && QDateTime::currentDateTime() > myRollOverTime) rollOver();

    FileAppender::append(timeStamp, logLevel, file, line, function, category, message);
} // end append
/******************************************************************************
** getDatePattern                                                             *
*******************************************************************************/
RollingFileAppender::DatePattern RollingFileAppender::getDatePattern() const
{
    QMutexLocker locker(&myRollingMutex);
    return myFrequency;
} // end getDatePattern
/******************************************************************************
** getDatePatternString                                                       *
*******************************************************************************/
QString RollingFileAppender::getDatePatternString() const
{
    QMutexLocker locker(&myRollingMutex);
    return myDatePatternString;
} // end getDatePatternString
/******************************************************************************
** setDatePattern                                                             *
*******************************************************************************/
void RollingFileAppender::setDatePattern(DatePattern datePattern)
{
    if (myDatePatternString != datePattern)
    {
        switch (datePattern)
        {
            case MinutelyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-MM-dd-hh-mm"));
                break;
            case HourlyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-MM-dd-hh"));
                break;
            case HalfDailyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-MM-dd-a"));
                break;
            case DailyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-MM-dd"));
                break;
            case WeeklyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-ww"));
                break;
            case MonthlyRollover:
                setDatePatternString(QLatin1String("'.'yyyy-MM"));
                break;
            default:
                Q_ASSERT_X(false, "DailyRollingFileAppender::setDatePattern()", "Invalid datePattern constant");
                setDatePattern(DailyRollover);
        };

        QMutexLocker locker(&myRollingMutex);
        myFrequency = datePattern;

        computeRollOverTime();
    }
} // end setDatePattern
/******************************************************************************
** setDatePattern                                                             *
*******************************************************************************/
void RollingFileAppender::setDatePattern(const QString &datePattern)
{
    if (myDatePatternString != datePattern)
    {
        setDatePatternString(datePattern);
        computeFrequency();
        computeRollOverTime();
    }
} // end setDatePattern
/******************************************************************************
** setDatePatternString                                                       *
*******************************************************************************/
void RollingFileAppender::setDatePatternString(const QString &datePatternString)
{
    if (myDatePatternString != datePatternString)
    {
        QMutexLocker locker(&myRollingMutex);
        myDatePatternString = datePatternString;
    }
} // end setDatePatternString
/******************************************************************************
** computeFrequency                                                           *
*******************************************************************************/
void RollingFileAppender::computeFrequency()
{
    QMutexLocker locker(&myRollingMutex);

    const QDateTime startTime(QDate(1999, 1, 1), QTime(0, 0));
    const QString startString = startTime.toString(myDatePatternString);

    if (startString != startTime.addSecs(60).toString(myDatePatternString))                 myFrequency = MinutelyRollover;
    else if (startString != startTime.addSecs(60 * 60).toString(myDatePatternString))       myFrequency = HourlyRollover;
    else if (startString != startTime.addSecs(60 * 60 * 12).toString(myDatePatternString))  myFrequency = HalfDailyRollover;
    else if (startString != startTime.addDays(1).toString(myDatePatternString))             myFrequency = DailyRollover;
    else if (startString != startTime.addDays(7).toString(myDatePatternString))             myFrequency = WeeklyRollover;
    else if (startString != startTime.addMonths(1).toString(myDatePatternString))           myFrequency = MonthlyRollover;
    else
    {
        Q_ASSERT_X(false, "DailyRollingFileAppender::computeFrequency", "The pattern '%1' does not specify a frequency");
        return;
    }
} // end computeFrequency
/******************************************************************************
** removeOldFiles                                                             *
*******************************************************************************/
void RollingFileAppender::removeOldFiles()
{
    if (myLogFilesLimit <= 1) return;

    QFileInfo fileInfo(getFileName());
    QDir logDirectory(fileInfo.absoluteDir());
    logDirectory.setFilter(QDir::Files);
    logDirectory.setNameFilters(QStringList() << fileInfo.fileName() + "*");
    QFileInfoList logFiles = logDirectory.entryInfoList();

    QMap<QDateTime, QString> fileDates;
    for (int i = 0; i < logFiles.length(); ++i)
    {
        QString name = logFiles[i].fileName();
        QString suffix = name.mid(name.indexOf(fileInfo.fileName()) + fileInfo.fileName().length());
        QDateTime fileDateTime = QDateTime::fromString(suffix, getDatePatternString());

        if (fileDateTime.isValid()) fileDates.insert(fileDateTime, logFiles[i].absoluteFilePath());
    }

    QList<QString> fileDateNames = fileDates.values();
    for (int i = 0; i < fileDateNames.length() - myLogFilesLimit + 1; ++i) QFile::remove(fileDateNames[i]);
} // end removeOldFiles
/******************************************************************************
** computeRollOverTime                                                        *
*******************************************************************************/
void RollingFileAppender::computeRollOverTime()
{
    Q_ASSERT_X(!myDatePatternString.isEmpty(), "DailyRollingFileAppender::computeRollOverTime()", "No active date pattern");

    QDateTime now = QDateTime::currentDateTime();
    QDate nowDate = now.date();
    QTime nowTime = now.time();
    QDateTime start;

    switch (myFrequency)
    {
        case MinutelyRollover:
        {
            start = QDateTime(nowDate, QTime(nowTime.hour(), nowTime.minute(), 0, 0));
            myRollOverTime = start.addSecs(60);
        }
            break;
        case HourlyRollover:
        {
            start = QDateTime(nowDate, QTime(nowTime.hour(), 0, 0, 0));
            myRollOverTime = start.addSecs(60*60);
        }
            break;
        case HalfDailyRollover:
        {
            int hour = nowTime.hour();
            if (hour >=  12)
                hour = 12;
            else
                hour = 0;
            start = QDateTime(nowDate, QTime(hour, 0, 0, 0));
            myRollOverTime = start.addSecs(60*60*12);
        }
            break;
        case DailyRollover:
        {
            start = QDateTime(nowDate, QTime(0, 0, 0, 0));
            myRollOverTime = start.addDays(1);
        }
            break;
        case WeeklyRollover:
        {
            // Qt numbers the week days 1..7. The week starts on Monday.
            // Change it to being numbered 0..6, starting with Sunday.
            int day = nowDate.dayOfWeek();
            if (day == Qt::Sunday) day = 0;
            start = QDateTime(nowDate, QTime(0, 0, 0, 0)).addDays(-1 * day);
            myRollOverTime = start.addDays(7);
        }
            break;
        case MonthlyRollover:
        {
            start = QDateTime(QDate(nowDate.year(), nowDate.month(), 1), QTime(0, 0, 0, 0));
            myRollOverTime = start.addMonths(1);
        }
            break;
        default:
            Q_ASSERT_X(false, "DailyRollingFileAppender::computeInterval()", "Invalid datePattern constant");
            myRollOverTime = QDateTime::fromTime_t(0);
    }

    myRollOverSuffix = start.toString(myDatePatternString);
    Q_ASSERT_X(now.toString(myDatePatternString) == myRollOverSuffix, "DailyRollingFileAppender::computeRollOverTime()", "File name changes within interval");
    Q_ASSERT_X(myRollOverSuffix != myRollOverTime.toString(myDatePatternString), "DailyRollingFileAppender::computeRollOverTime()", "File name does not change with rollover");
} // end computeRollOverTime
/******************************************************************************
** rollOver                                                                   *
*******************************************************************************/
void RollingFileAppender::rollOver()
{
    Q_ASSERT_X(!myDatePatternString.isEmpty(), "DailyRollingFileAppender::rollOver()", "No active date pattern");

    QString rollOverSuffix = myRollOverSuffix;
    computeRollOverTime();
    if (rollOverSuffix == myRollOverSuffix) return;

    closeFile();

    QString targetFileName = getFileName() + rollOverSuffix;
    QFile f(targetFileName);
    if (f.exists() && !f.remove())  return;
    f.setFileName(getFileName());
    if (!f.rename(targetFileName))  return;

    openFile();
    removeOldFiles();
} // end rollOver
/******************************************************************************
** setLogFilesLimit                                                           *
*******************************************************************************/
void RollingFileAppender::setLogFilesLimit(int limit)
{
    if (myLogFilesLimit != limit)
    {
        QMutexLocker locker(&myRollingMutex);
        myLogFilesLimit = limit;
    }
} // end setLogFilesLimit
/******************************************************************************
** getLogFilesLimit                                                           *
*******************************************************************************/
int RollingFileAppender::getLogFilesLimit() const
{
    QMutexLocker locker(&myRollingMutex);
    return myLogFilesLimit;
} // end getLogFilesLimit
/******************************* End of File *********************************/
