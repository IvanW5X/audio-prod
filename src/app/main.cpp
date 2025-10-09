/************************************************************
 * File: main.cpp
 * 
 * Description: Entry file for audio production tool
 * 
 * Date: 2025-10-06
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#define TEST

int main(int argc, char *argv[])
{
    #ifndef TEST

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;

    QGuiApplication::setOrganizationName("My super cool known organization");
    QGuiApplication::setApplicationName("Audio Prod");

    QObject::connect(&qmlEngine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    QObject::connect(&qmlEngine, &QQmlApplicationEngine::objectCreationFailed, &app, []
    {
        qCritical() << "Error: Failed to load";
        QCoreApplication::exit(EXIT_FAILURE); 
    },
    Qt::QueuedConnection);

    qmlEngine.loadFromModule("AudioProd.Main", "Main");

    if (qmlEngine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
    
    #else

    

    return 0;

    #endif
}
