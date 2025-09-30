/**********************************************************
 * Description: Implementation file for utilities
 * 
 * Date: 2025-09-26
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "utils.h"

// Returns a bool if the selected file can be loaded without any issues
bool Utils::isValidAudioFile(const QString &FileName)
{
    const QFileInfo FileInfo = QFileInfo(FileName);
    const bool IsFileExists = (!FileName.isEmpty()) && (FileInfo.exists());

    if (!IsFileExists) return false;

    QAudioDecoder decoder;
    QEventLoop loop;
    bool success = false;

    (void) QObject::connect(&decoder, &QAudioDecoder::bufferReady, [&]()
    {
        QAudioBuffer buffer = decoder.read();
        if (!buffer.isValid()) {
            success = false;
        } else {
            success = true;
        }
        decoder.stop();
        loop.quit();
    });

    (void) QObject::connect(&decoder, &QAudioDecoder::finished, [&]()
    {
        loop.quit();
    });

    (void) QObject::connect(&decoder, QOverload<QAudioDecoder::Error>::of(&QAudioDecoder::error),[&](QAudioDecoder::Error error)
    {
        success = false;
        loop.quit();
    });

    decoder.setSource(QUrl::fromLocalFile(FileName));
    decoder.start();

    loop.exec();  // Wait until we either get a buffer, error, or finished

    return success;
}
