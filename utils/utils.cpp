/**********************************************************
 * Description: Implementation file for utilities
 * 
 * Date: 2025-09-26
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "utils.h"

// Sets up application before starting
void Utils::setupApp()
{
    qRegisterMetaType<AudioCommand::RequestPtr>();
    qRegisterMetaType<AudioCommand::RequestPtr>();
}

bool Utils::isValidAudioFile(const QString &FileName)
{
    const QFileInfo Info = QFileInfo(FileName);
    bool isValid = true;

    if (!Info.exists())
    {
        isValid = false;
    }
    else
    {
        const char *FileName_cstr = FileName.toStdString().c_str();
        TagLib::FileRef ref = TagLib::FileRef(FileName_cstr);

        if (!ref.audioProperties())
        {
            isValid = false;
        }
        qDebug() << ref.audioProperties()->sampleRate();
    }
    return true;
}
