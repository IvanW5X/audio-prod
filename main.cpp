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

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MainWindow window;
    int32_t returnValue = 0;

    window.show();

    returnValue = app.exec();

    return returnValue;
}
