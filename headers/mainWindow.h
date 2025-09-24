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
#include <QFileDialog>

#define DEBUG

#ifdef DEBUG
#include <iostream>
#endif

namespace Ui
{
    class MainWindow;
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
        void audioFileSelected(const QString FileName);

    private slots:
        void onOpenAudioFileClicked();

    public slots:

    private:
        // Member variables
        Ui::MainWindow *ui;

        // Disable copy constructor and assignment operator overload
        MainWindow(const MainWindow &) = delete;
        MainWindow &operator=(const MainWindow &) = delete;
};
