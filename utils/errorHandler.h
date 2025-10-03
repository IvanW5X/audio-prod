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

#include <QObject>
#include <QMap>

namespace Error
{
    enum Id : uint32_t
    {
        InvalidAudioFile = 1001
    };
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
        static const QMap<const Error::Id, const QString> ErrorMessages;
    
    private:
        explicit ErrorHandler(QObject *parent = nullptr);
        ~ErrorHandler();
};

Q_DECLARE_METATYPE(Error::Id)
