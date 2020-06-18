#pragma once
/******************************************************************************
 @brief QLogger is a library to register and print logs into a file.
 @see LinkedIn: www.linkedin.com/in/cescmm/
 @see Web: www.francescmm.com
 ******************************************************************************/
#include <QObject>
#include <QMetaEnum>

class QLoggerLevel
{
        Q_GADGET

    public:
        /*!
         * \enum LogLevel
         * \brief The LogLevel class enum LogLevel defines the level of the log message.
         * \code QLoggerLevel::LogLevel::Debug \endcode
         */
        enum LogLevel
        {
            Trace = 0,  //!< \c Trace    \brief Trace level is used for internal code tracing.
            Debug,      //!< \c Debug    \brief Debug level is used for writing custom debug output.
            Info,       //!< \c Info     \brief Info level is used for informational messages.
            Event,      //!< \c Event    \brief Event level is used for logging events, like: login, http requests.
            Warning,    //!< \c Warning  \brief Warning level is used to report warnings and recoverable errors in your application.
            Error,      //!< \c Error    \brief Error level is used for writing critical error messages and reporting system errors.
            Critical,   //!< \c Critical \brief Critical level is used for writing critical error messages and reporting system errors more sever than Error.
            Fatal       //!< \c Fatal    \brief Fatal level is used for writing fatal error messages shortly before exiting.
        };

        Q_ENUM(LogLevel)

        /*!
            \fn static QString levelToText(const QLoggerLevel::LogLevel &value)
            \brief Level Number to Text.
            \param value \c QLoggerLevel::LogLevel is name of the enum.
         */
        static QString levelToText(const QLoggerLevel::LogLevel &value)
        {
            auto metaEnum = QMetaEnum::fromType<QLoggerLevel::QLoggerLevel::LogLevel>();
            // FIXME Translation
            return QString(metaEnum.valueToKey(value));
        }
}; // end class QLoggerLevel
/******************************* End of File *********************************/

