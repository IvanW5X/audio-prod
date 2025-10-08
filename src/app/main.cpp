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

#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine qmlEngine;
    int32_t returnVal = 0;

    QObject::connect(&qmlEngine, &QQmlApplicationEngine::quit, &app, &QGuiApplication::quit);
    QObject::connect(&qmlEngine, &QQmlApplicationEngine::objectCreationFailed, &app, []
    { 
        qCritical() << "Error: Failed to load";
        QCoreApplication::exit(-1); 
    },
    Qt::QueuedConnection);

    qmlEngine.loadFromModule("AudioProd.Main", "Main");
    returnVal = app.exec();

    return returnVal;
}
