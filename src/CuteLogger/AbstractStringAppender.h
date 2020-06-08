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
#ifndef ABSTRACTSTRINGAPPENDER_H
#define ABSTRACTSTRINGAPPENDER_H

// Local
#include "CuteLogger_global.h"
#include <AbstractAppender.h>

// Qt
#include <QReadWriteLock>

/******************************************************************************
** class AbstractStringAppender                                               *
*******************************************************************************/
class CUTELOGGERSHARED_EXPORT AbstractStringAppender : public AbstractAppender
{
    public:
        AbstractStringAppender();

        virtual QString format() const;
        void setFormat(const QString &format);

        static QString stripFunctionName(const char *name);

    protected:
        QString formattedString(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line, const char *function, const QString &category, const QString &message) const;

    private:
        static QByteArray qCleanupFuncinfo(const char *name);

        QString myFormat;
        mutable QReadWriteLock myFormatLock;
}; // end AbstractStringAppender
#endif // ABSTRACTSTRINGAPPENDER_H
/******************************* End of File *********************************/
