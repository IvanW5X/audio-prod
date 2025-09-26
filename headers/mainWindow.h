/**********************************************************
 * Description: Header file for the Main Window
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#pragma once

#include <QMainWindow>
#include "audioPlayer.h"

namespace Ui
{
    class MainWindow;
}

// Stacked widget pages
namespace Pages
{
    enum Pages_T
    {
        Home = 0,
        Documentation,
        AudioPlayer
    };
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        // Constructor and Destructor
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

        // Public APIs
        void init();

    signals:
        void audioFileSelected(const QString &FileName);
              
    public slots:
    
    private slots:
        void onHomePageClicked();
        void onDocumentationClicked();
        void onOpenAudioFileClicked();

    private:
        // Member variables
        Ui::MainWindow *ui;
        AudioPlayer *audioPlayer;

        // Helper functions
        void changePage(const Pages::Pages_T NewPage);

        // Disable copy constructor and assignment operator overload
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;
};
