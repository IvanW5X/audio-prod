/**********************************************************
 * Description: Implementation file for the Main Window
 *
 * Date: 2025-09-22
 *
 * Author: Ivan Wong
 *
 **********************************************************/

#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QFileDialog>

// Constructor, initializes the UI
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    audioPlayer(new AudioPlayer(this))
{
    // Setup UI elements
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(Pages::Home);

    // Note: The home page and documentation page area already in the stacked widget
    //       by default in the .ui file
    // Add other pages
    ui->stackedWidget->addWidget(audioPlayer);
}

// Destructor, frees memory
MainWindow::~MainWindow()
{
    delete ui;
    delete audioPlayer;
}

// Initializes the main window
void MainWindow::init()
{
    // Initialize member variables
    audioPlayer->init();

    // Connect UI triggers with slots
    (void) connect(ui->actionOpen_Audio_File, &QAction::triggered, this, &MainWindow::onOpenAudioFileClicked);

    // Connect custom signals with slots
    (void) connect(this, &MainWindow::audioFileSelected, audioPlayer, &AudioPlayer::updateUiWithAudioFile);

}

// Gets the name of the selected audio file and emits a signal when successful
void MainWindow::onOpenAudioFileClicked()
{
    const QString FilePath = QFileDialog::getOpenFileName(this,
                                                          tr("Select Audio File"),
                                                          QDir::homePath(),
                                                          tr("Audio Files (*.mp3 *.wav *.flac);;All Files (*.*)"));

    if (!FilePath.isEmpty())
    {
        ui->stackedWidget->setCurrentIndex(Pages::AudioPlayer);
        emit audioFileSelected(FilePath);
    }
}
