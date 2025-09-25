/**********************************************************
 * Description: Header file for the audio player controller.
 * Manages the audio playback controls using inputs from the user 
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QWidget>

namespace Ui
{
    class AudioController;
}

class AudioController : public QWidget
{
    Q_OBJECT

    public:
        explicit AudioController(QWidget *parent = nullptr);
        ~AudioController();
        
    private:
};
