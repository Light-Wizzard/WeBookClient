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
#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H

// Logger
#include "CuteLogger_global.h"
#include <AbstractStringAppender.h>

// Qt
#include <QFile>
#include <QTextStream>

/******************************************************************************
** class FileAppender                                                         *
*******************************************************************************/
class CUTELOGGERSHARED_EXPORT FileAppender : public AbstractStringAppender
{
    public:
        FileAppender(const QString &getFileName = QString());
        ~FileAppender();

        QString getFileName() const;
        void setFileName(const QString &logName);

        bool reopenFile();

    protected:
        virtual void append(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line, const char *function, const QString &category, const QString &message) override;
        bool openFile();
        void closeFile();

    private:
        QFile           myLogFileHandle;
        QTextStream     myLogStream;
        mutable QMutex  myLogFileMutex;

}; // end FileAppender
#endif // FILEAPPENDER_H
/******************************* End of File *********************************/
