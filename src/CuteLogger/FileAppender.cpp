/*
  Copyright (c) 2010 Boris Moiseev (cyberbobs at gmail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/
// Local
#include "FileAppender.h"

// STL
#include <iostream>
/******************************************************************************
** FileAppender Constructor                                                   *
*******************************************************************************/
/**
 * \class FileAppender
 *
 * \brief Simple appender that writes the log records to the plain text file.
 */
//! Constructs the new file appender assigned to file with the given name.
FileAppender::FileAppender(const QString &fileName)
{
    setFileName(fileName);
} // end FileAppender
/******************************************************************************
** FileAppender Deconstructor                                                 *
*******************************************************************************/
FileAppender::~FileAppender()
{
    closeFile();
} // end FileAppender
/******************************************************************************
** getFileName                                                                *
*******************************************************************************/
//! Returns the name set by setFileName() or to the FileAppender constructor.
/**
 * \sa setFileName()
 */
QString FileAppender::getFileName() const
{
    QMutexLocker locker(&myLogFileMutex);
    return myLogFileHandle.fileName();
} // end getFileName
/******************************************************************************
** setFileName                                                                *
*******************************************************************************/
//! Sets the name of the file. The name can have no path, a relative path, or an absolute path.
/**
 * \sa fileName()
 */
void FileAppender::setFileName(const QString &logName)
{
    if (logName.isEmpty()) std::cerr << "<FileAppender::FileAppender> File name is empty. The appender will do nothing" << std::endl;

    QMutexLocker locker(&myLogFileMutex);
    if (myLogFileHandle.isOpen()) myLogFileHandle.close();

    myLogFileHandle.setFileName(logName);
} // end setFileName
/******************************************************************************
** reopenFile                                                                 *
*******************************************************************************/
bool FileAppender::reopenFile()
{
    closeFile();
    return openFile();
} // end reopenFile
/******************************************************************************
** openFile                                                                   *
*******************************************************************************/
bool FileAppender::openFile()
{
    if (myLogFileHandle.fileName().isEmpty()) return false;

    bool isOpen = myLogFileHandle.isOpen();
    if (!isOpen)
    {
        isOpen = myLogFileHandle.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
        if (isOpen)  myLogStream.setDevice(&myLogFileHandle);
        else         std::cerr << "<FileAppender::append> Cannot open the log file " << qPrintable(myLogFileHandle.fileName()) << std::endl;
    }
    return isOpen;
} // end openFile
/******************************************************************************
** append                                                                     *
*******************************************************************************/
//! Write the log record to the file.
/**
 * \sa fileName()
 * \sa AbstractStringAppender::format()
 */
void FileAppender::append(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line, const char *function, const QString &category, const QString &message)
{
    QMutexLocker locker(&myLogFileMutex);

    if (openFile())
    {
        myLogStream << formattedString(timeStamp, logLevel, file, line, function, category, message);
        myLogStream.flush();
        myLogFileHandle.flush();
    }
} // end append
/******************************************************************************
** closeFile                                                                  *
*******************************************************************************/
void FileAppender::closeFile()
{
    QMutexLocker locker(&myLogFileMutex);
    myLogFileHandle.close();
} // end closeFile
/******************************* End of File *********************************/
