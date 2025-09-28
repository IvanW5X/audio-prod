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

#include "waveForm.h"
#include "audioPlayer.h"

#define DEBUG

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    int32_t returnValue = 0;

#ifndef DEBUG

    window.init();

    // TODO: add loading screen with animation before showing app
    
    window.show();

#else

    WaveForm waveForm;
    waveForm.init();

    waveForm.show();

#endif // DEBUG

    returnValue = app.exec();

    return returnValue;
}
