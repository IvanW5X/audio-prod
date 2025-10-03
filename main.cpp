/**********************************************************
 * Description: Main file for audio production tool
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#include "mainWindow.h"
#include "commands.h"
#include "audioController.h"
#include "utils.h"
#include <QApplication>

#include "audioEngine.h"

#define DEBUG


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    int32_t returnValue = 0;

    Utils::setupApp();

#ifndef DEBUG
    AudioController::instance().init();
    window.init();

    // TODO: add loading screen with animation before showing app
    
    window.show();

#else

#endif // DEBUG

    returnValue = app.exec();

    return returnValue;
}
