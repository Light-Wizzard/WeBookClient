#pragma once

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

#define LOGLEVEL_CLASS

#ifdef LOGLEVEL_CLASS

#include <QObject>
#include <QMetaEnum>

namespace QLogger
{
    class QLoggerLevel
    {
            Q_GADGET

        public:
            /**
             * @brief The LogLevel enum class defines the level of the log message.
             * QLoggerLevel::LogLevel::Trace
             */
            enum LogLevel
            {
                Trace = 0,  //! \c Trace \brief Trace level is used for internal code tracing.
                Debug,      //! \c Debug \brief Debug level is used for writing custom debug output.
                Info,       //! \c Info \brief Info level is used for informational messages.
                Event,       //! \c Info \brief Event level is used for logging events, like: login, http requests...
                Warning,    //! \c Warning \brief Warning level is used to report warnings and recoverable errors in your application.
                Error,      //! \c Error \brief Error level is used for writing critical error messages and reporting system errors.
                Critical,   //! \c Critical \brief Critical level is used for writing critical error messages and reporting system errors more sever than Error.
                Fatal       //! \c Fatal \brief Fatal level is used for writing fatal error messages shortly before exiting.
            };

            Q_ENUM(LogLevel)

            static QString levelToText(const QLoggerLevel::LogLevel &value)
            {
                auto metaEnum = QMetaEnum::fromType<QLoggerLevel::QLoggerLevel::LogLevel>();
                return QString(metaEnum.valueToKey(value));
            }
    }; // end class QLogger
} // end namespace QLogger
#else
namespace QLogger
{

    /**
     * @brief The LogLevel enum class defines the level of the log message.
     */
    enum class LogLevel
    {
        Trace = 0,
        Debug,
        Info,
        Warning,
        Error,
        Fatal
    };
}
#endif

