/**********************************************************
 * Description: Implementation file for the Error Handler.
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "errorHandler.h"

// Map of all error IDs with a generic error message
const QMap<Error::Id, QString> ErrorMessages = 
{
    { Error::InvalidAudioFile, "File not found, access denied, or invalid audio file." },
    { Error::DecodingFailed, "Audio decoding failed" },
    { Error::Unknown, "Unknown internal error" }    // Set errors in order relative to Error::Id enum
};

ErrorHandler::ErrorHandler(QObject *parent) : QObject(parent)
{

}

ErrorHandler::~ErrorHandler()
{

}

void ErrorHandler::handleError(const Error::Id ErrorId, const QString &Context)
{
    
    QString errorMessage;

    if (!ErrorMessages.contains(ErrorId))
    {
        errorMessage = ErrorMessages[Error::Unknown];
    }
    else
    {
        errorMessage = ErrorMessages[ErrorId];
    }
    // TODO: add more robust error display
    qDebug() << ErrorId << ": " << errorMessage << " " << Context;
}
