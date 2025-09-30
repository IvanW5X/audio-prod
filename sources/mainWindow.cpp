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

// Constructor, initializes the UI
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    audioPlayer(new AudioPlayerWidget(this))
{
    // Setup UI elements
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(Pages::Home);

    // Note: The home page and documentation page area already in the stacked widget
    //       by default in the .ui file, so no need to add them in
    ui->stackedWidget->addWidget(audioPlayer);
}

// Destructor, frees memory
MainWindow::~MainWindow()
{
    delete ui;
}

// Initializes the main window
void MainWindow::init()
{
    // Initialize member variables
    audioPlayer->init();

    (void) connect(ui->actionHome_Page, &QAction::triggered, this, &MainWindow::onHomePageClicked);
    (void) connect(ui->actionDocumentation, &QAction::triggered, this, &MainWindow::onDocumentationClicked);
    (void) connect(ui->actionOpen_Audio_File, &QAction::triggered, this, &MainWindow::onOpenAudioFileClicked);
    (void) connect(this, &MainWindow::audioFileSelected, audioPlayer, &AudioPlayerWidget::onUpdateAudioPlayer);
}

// Directs the user to the home page using the menu bar
void MainWindow::onHomePageClicked()
{
    // TODO: add some logic here before going to home page;
    changePage(Pages::Home);
}

// TODO: Figure out implementation details for this
void MainWindow::onDocumentationClicked()
{
    changePage(Pages::Documentation);
}

// Gets the name of the selected audio file and emits a signal when successful
void MainWindow::onOpenAudioFileClicked()
{
    const QString FileName = QFileDialog::getOpenFileName(this,
                                                          tr("Select Audio File"),
                                                          QDir::homePath(),
                                                          tr("Audio Files (*.mp3 *.wav *.flac);;All Files (*.*)"));

    if (Utils::isValidAudioFile(FileName))
    {
        changePage(Pages::AudioPlayer);
        emit audioFileSelected(FileName);
    }
    else
    {
        // TODO: error handle
    }
}

// Handles logic that needs to happen before switching pages
void MainWindow::changePage(const Pages::Pages_T NewPage)
{
    const int32_t CurrentPage = ui->stackedWidget->currentIndex();

    if (CurrentPage == Pages::Home)
    {
        ui->stackedWidget->setCurrentIndex(NewPage);
    }
    else if (CurrentPage == Pages::Documentation)
    {
        ui->stackedWidget->setCurrentIndex(NewPage);
    }
    else if (CurrentPage == Pages::AudioPlayer)
    {
        // TODO:
        // is an audio loaded in the media player?
            // reset audio player and output -- function from audioPlayer

        ui->stackedWidget->setCurrentIndex(NewPage);
    }
}