/**********************************************************
 * Description: Main file for audio production tool
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#include <QApplication>
#include "mainWindow.h"
#include "commonDefines.h"

#include "audioController.h"
#include "audioEngine.h"

// #define DEBUG

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    int32_t returnValue = 0;

#ifndef DEBUG

    AudioController::Instance().init();
    window.init();

    // TODO: add loading screen with animation before showing app
    
    window.show();

#else
    SyncedAudioQueue buffer;
    AudioEngine engine = AudioEngine(&buffer, nullptr);
    engine.init();

    engine.test();

#endif // DEBUG

    returnValue = app.exec();

    return returnValue;
}
