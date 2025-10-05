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
const QMap<Error::Id, QString> ErrorHandler::ErrorMessages = 
{
    // Add error messages in sequence with the Error ID enum
    // Not necessary, but keeps it more organized
    { Error::InvalidAudioFile, "File not found, access denied, or invalid audio file." },
    { Error::DecodingFailed, "Audio decoding failed." },
    { Error::ReadingFileFailed, "File could not be read." },
    { Error::DataNotFound, "Requested data could not be found." },
    { Error::UnknownRequest, "Unknown request." },
    { Error::Unknown, "Unknown internal error." }
};

// Constructor
ErrorHandler::ErrorHandler(QObject *parent) :
    QObject(parent)
{

}

// Destructor
ErrorHandler::~ErrorHandler()
{

}

// Displays the error Id string, detail, and context from where/why the error occurred
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
    qDebug() << ": " << errorMessage << " " << Context;
}
