/**********************************************************
 * Description: Main file for audio production tool
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#include "mainWindow.h"
#include "utils.h"
#include "audioController.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    int32_t returnValue = 0;

    Utils::setupApp();

    AudioController::instance().init();
    window.init();

    // TODO: add loading screen with animation before showing app
    
    window.show();

    returnValue = app.exec();

    return returnValue;
}
