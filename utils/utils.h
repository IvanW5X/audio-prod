/**********************************************************
 * Description: Common data and functions for the audio production tool
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QObject>
#include <QAudioDecoder>
#include <QUrl>
#include <QFileInfo>
#include <QEventLoop>

namespace Utils
{
    bool isValidAudioFile(const QString &FileName);
}