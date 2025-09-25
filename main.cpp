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
#include "audioPlayer.h"
#include "commonDefines.h"

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

    AudioPlayer player;
    player.init();
    player.show();

#endif // DEBUG

    returnValue = app.exec();

    return returnValue;
}
