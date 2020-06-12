#ifndef QLOGGERWRAPPER_H
#define QLOGGERWRAPPER_H
/****************************************************************************************
 ** QLogger is a library to register and print logs into a file.
 **
 ** LinkedIn: www.linkedin.com/in/cescmm/
 ** Web: www.francescmm.com
 **
 ** This lbirary is free software; you can redistribute it and/or
 ** modify it under the terms of the GNU Lesser General Public
 ** License as published by the Free Software Foundation; either
 ** version 2 of the License, or (at your option) any later version.
 **
 ** This library is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 ** Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public
 ** License along with this library; if not, write to the Free Software
 ** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ***************************************************************************************/

#include <QString>
#include <QDebug>

#include "QLogger.h"

// Define if using as Libary
#if defined(QLOGGER_LIBRARY)
#  define QLOGGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QLOGGERSHARED_EXPORT Q_DECL_IMPORT
#endif
/******************************************************************************
** namespace QLogger                                                          *
*******************************************************************************/
namespace QLogger
{
    /******************************************************************************
    ** class QLoggerWrapper                                                       *
    *******************************************************************************/
    class QLOGGERSHARED_EXPORT QLoggerWrapper
    {
            Q_DISABLE_COPY(QLoggerWrapper)

        public:
            QLoggerWrapper(const QString &thisModule, const QString &thisLogPath, QLoggerLevel::LogLevel level, const char *file, int line, const char *function);
            ~QLoggerWrapper();

            void write(const char* msg, ...)
            #if defined(Q_CC_GNU) && !defined(__INSURE__)
            #  if defined(Q_CC_MINGW) && !defined(Q_CC_CLANG)
                __attribute__ ((format (gnu_printf, 2, 3)))
            #  else
                __attribute__ ((format (printf, 2, 3)))
            #  endif
            #endif
            ;
            void write(const QString &msg);
            QDebug write();

        private:
            // Define in order of init
            QString                 myModule;
            QString                 myLogPath;
            QString                 myMessage;
            QLoggerLevel::LogLevel  myLogLevel;
            const char              *myFile;
            int                     myLine;
            const char              *myFunction;

    }; // end class QLoggerWrapper
} // end namespace QLogger

#  define Q_FUNC_INFO       __PRETTY_FUNCTION__
//#  define Q_ALIGNOF(type)   __alignof__(type)
#  define Q_TYPEOF(expr)    __typeof__(expr)
#  define Q_DECL_DEPRECATED __attribute__ ((__deprecated__))
//#  define Q_DECL_ALIGN(n)   __attribute__((__aligned__(n)))
#  define Q_DECL_UNUSED     __attribute__((__unused__))
#  define Q_LIKELY(expr)    __builtin_expect(!!(expr), true)
#  define Q_UNLIKELY(expr)  __builtin_expect(!!(expr), false)
#  define Q_NORETURN        __attribute__((__noreturn__))
//#  define Q_REQUIRED_RESULT __attribute__ ((__warn_unused_result__))
#  define Q_DECL_PURE_FUNCTION __attribute__((pure))
#  define Q_DECL_CONST_FUNCTION __attribute__((const))
#  define Q_DECL_COLD_FUNCTION __attribute__((cold))
#  if !defined(QT_MOC_CPP)
#    define Q_PACKED __attribute__ ((__packed__))
#    ifndef __ARM_EABI__
#      define QT_NO_ARM_EABI
#    endif
#  endif
#  if Q_CC_GNU >= 403 && !defined(Q_CC_CLANG)
#      define Q_ALLOC_SIZE(x) __attribute__((alloc_size(x)))
#  endif

// FIXME not the way to do it
static QString myModule = "WeBookClient";
static QString myLogPath = "logs";
#define QLOG_TRACE      QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Trace,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_DEBUG      QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Debug,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_INFO       QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Info,    __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_WARNING    QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Warning, __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_ERROR      QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_FATAL      QLogger::QLoggerWrapper(myModule, myLogPath, QLogger::QLoggerLevel::LogLevel::Fatal,   __FILE__, __LINE__, Q_FUNC_INFO).write

#endif // QLOGGERWRAPPER_H
/* ***************************** End of File ******************************* */

