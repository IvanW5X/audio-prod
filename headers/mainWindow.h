/**********************************************************
 * Description: Header file for the Main Window
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#pragma once

#include "audioController.h"
#include "audioPlayerWidget.h"
#include "errorHandler.h"
#include "utils.h"
#include <QMainWindow>
#include <QFileDialog>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        enum Pages_T
        {
            Home = 0,
            Documentation,
            AudioPlayer
        };
        Q_ENUM(Pages_T)

        // Constructor and Destructer
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Public APIs
        void init();

    signals:
              
    public slots:
        //DEBUG
        void test(const AudioData::MetaDataMap_T &map);
    
    private slots:
        void onHomePageClicked();
        void onDocumentationClicked();
        void onOpenAudioFileClicked();

    private:

        // Member variables
        Ui::MainWindow *ui;
        AudioPlayerWidget *audioPlayer;

        // Helper functions
        void changePage(const Pages_T NewPage);

        // Disable copy constructor and assignment operator overload
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;
};
