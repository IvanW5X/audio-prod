/************************************************************
 * FILE: main.qml
 * 
 * DESCRIPTION: Entry UI file for audio production tool
 * 
 * DATE: 2025-10-06
 *
 * AUTHOR: Ivan Wong
 *
 ************************************************************/

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow
{
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Audio Prod")

    Button
    {
        id: todo_test_button
        width: 100
        height: 50
        anchors.centerIn: parent
    }
}
