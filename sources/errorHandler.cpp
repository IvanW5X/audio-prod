/**********************************************************
 * Description: Implementation file for the Error Handler.
 * 
 * Date: 2025-09-29
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "errorHandler.h"

// Map of all error IDs
QMap<const Error::Id, const QString> ErrorMessages = 
{
    { Error::InvalidAudioFile, "File not found, access denied, or invalid audio file." }
};

ErrorHandler::ErrorHandler(QObject *parent) :
    QObject(parent)
{

}

ErrorHandler::~ErrorHandler()
{

}
