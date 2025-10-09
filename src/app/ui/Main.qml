/************************************************************
 * File: main.qml
 * 
 * Description: Entry UI file for audio production tool
 * 
 * Date: 2025-10-06
 * 
 * Author: Ivan Wong
 * 
 ************************************************************/

import QtQuick
// import QtQuick.Controls
import QtQuick.Layouts

Window
{
    id: root
    width: 800
    height: 600
    visible: true
    title: qsTr("Audio Prod")

    Item
    {
        id: quickListButtons
        width: 400
        height: 300

        GridLayout
        {
            anchors.centerIn: parent
            columns: 2
            rowSpacing: 10
            layoutDirection: Qt.LeftToRight
            uniformCellHeights: true
            uniformCellWidths: true
        }

    }
}
