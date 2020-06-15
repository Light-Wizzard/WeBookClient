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

#include "QLoggerManager.h"
#include "QLogger/QLoggerCommon.h"

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
#ifdef LOGLEVEL_CLASS
            QLoggerWrapper(QLoggerLevel::LogLevel level, const char *file, int line, const char *function);
#else
            QLoggerWrapper(LogLevel level, const char *file, int line, const char *function);
#endif
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
#ifdef LOGLEVEL_CLASS
            QLoggerLevel::LogLevel  myLogLevel;
#else
            LogLevel  myLogLevel;
#endif
            const char              *myFile;
            int                     myLine;
            const char              *myFunction;

    }; // end class QLoggerWrapper
} // end namespace QLogger

#ifndef Q_FUNC_INFO
#  define Q_FUNC_INFO       __PRETTY_FUNCTION__
#endif

#ifndef Q_ALIGNOF
//#  define Q_ALIGNOF(type)   __alignof__(type)
#endif
#ifndef Q_TYPEOF
#  define Q_TYPEOF(expr)    __typeof__(expr)
#endif
#ifndef Q_DECL_DEPRECATED
#  define Q_DECL_DEPRECATED __attribute__ ((__deprecated__))
#endif
#ifndef Q_DECL_ALIGN
#  define Q_DECL_ALIGN(n)   __attribute__((__aligned__(n)))
#endif
#ifndef Q_DECL_UNUSED
#  define Q_DECL_UNUSED     __attribute__((__unused__))
#endif
#ifndef Q_LIKELY
#  define Q_LIKELY(expr)    __builtin_expect(!!(expr), true)
#endif
#ifndef Q_UNLIKELY
#  define Q_UNLIKELY(expr)  __builtin_expect(!!(expr), false)
#endif
#ifndef Q_NORETURN
#  define Q_NORETURN        __attribute__((__noreturn__))
#endif
#ifndef Q_REQUIRED_RESULT
#  define Q_REQUIRED_RESULT __attribute__ ((__warn_unused_result__))
#endif
#ifndef Q_DECL_PURE_FUNCTION
#  define Q_DECL_PURE_FUNCTION __attribute__((pure))
#endif
#ifndef Q_DECL_CONST_FUNCTION
#  define Q_DECL_CONST_FUNCTION __attribute__((const))
#endif
#ifndef Q_DECL_COLD_FUNCTION
#  define Q_DECL_COLD_FUNCTION __attribute__((cold))
#endif

#  if !defined(QT_MOC_CPP)
#    define Q_PACKED __attribute__ ((__packed__))
#    ifndef __ARM_EABI__
#      define QT_NO_ARM_EABI
#    endif
#  endif
#  if Q_CC_GNU >= 403 && !defined(Q_CC_CLANG)
#      define Q_ALLOC_SIZE(x) __attribute__((alloc_size(x)))
#  endif

#ifdef LOGLEVEL_CLASS

#define QLOG_TRACE      QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Trace,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_DEBUG      QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Debug,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_EVENT      QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_INFO       QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Info,    __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_WARNING    QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Warning, __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_ERROR      QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_CRITICAL   QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_FATAL      QLogger::QLoggerWrapper(QLogger::QLoggerLevel::LogLevel::Fatal,   __FILE__, __LINE__, Q_FUNC_INFO).write

#else

#define QLOG_TRACE      QLogger::QLoggerWrapper(QLogger::LogLevel::Trace,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_DEBUG      QLogger::QLoggerWrapper(QLogger::LogLevel::Debug,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_EVENT      QLogger::QLoggerWrapper(QLogger::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_INFO       QLogger::QLoggerWrapper(QLogger::LogLevel::Info,    __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_WARNING    QLogger::QLoggerWrapper(QLogger::LogLevel::Warning, __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_ERROR      QLogger::QLoggerWrapper(QLogger::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_CRITICAL   QLogger::QLoggerWrapper(QLogger::LogLevel::Error,   __FILE__, __LINE__, Q_FUNC_INFO).write
#define QLOG_FATAL      QLogger::QLoggerWrapper(QLogger::LogLevel::Fatal,   __FILE__, __LINE__, Q_FUNC_INFO).write

#endif


#endif // QLOGGERWRAPPER_H
/* ***************************** End of File ******************************* */

