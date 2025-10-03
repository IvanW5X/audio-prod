/**********************************************************
 * Description: Common data and functions for the audio production tool
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include "commands.h"
#include <QString>
#include <QFileInfo>
#include <taglib/fileref.h>

namespace Utils
{
    void setupApp();
    bool isValidAudioFile(const QString &FileName);
}