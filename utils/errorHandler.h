/**********************************************************
 * Description: Header file for the error handler. This class
 * is responsible for providing custom error codes/details
 * to display for the user. Uses the singleton design
 * pattern to prevent any 
 * 
 * Also helpful class for debugging issues during development
 * 
 * Date: 2025-10-02
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "utils.h"
#include <QObject>
#include <QMap>
#include <QDebug>

namespace Error
{
    Q_NAMESPACE
    enum Id : uint32_t
    {
        InvalidAudioFile = 1001u,
        ReadingFileFailed,
        DecodingFailed,
        DataNotFound,
        UnknownRequest,
        Unknown = 9999u     // Must be the last error id
    };
    Q_ENUM_NS(Error::Id)
}

class ErrorHandler : public QObject
{
    Q_OBJECT

    public:
        // Thread safe as of C++11
        static ErrorHandler &instance()
        {
            static ErrorHandler instance;
            return instance;
        }
        static const QMap<Error::Id, QString> ErrorMessages;
    
        void handleError(const Error::Id ErrorId, const QString &Context);

    private:
        // Prevent direct instantiation
        explicit ErrorHandler(QObject *parent = nullptr);
        ~ErrorHandler();

        // Helper functions
        QString errorIdToString(const Error::Id ErrorId);

        // Disable copy constructor and assignment operator overload
        ErrorHandler(const ErrorHandler &) = delete;
        ErrorHandler &operator=(const ErrorHandler &) = delete;
};

Q_DECLARE_METATYPE(Error::Id)
