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
    ui(new Ui::MainWindow)
{
    // Setup UI elements
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    this->setWindowTitle("Audio Production");
}

// Destructor, deletes the UI
MainWindow::~MainWindow()
{
    delete ui;
}

// Initializes the main window
void MainWindow::init()
{
    // Connect signals and slots
    (void)connect(ui->actionOpen_Audio_File, &QAction::triggered, this, &MainWindow::onOpenAudioFileClicked);
}

// Gets the name of the selected audio file and emits a signal when successful
void MainWindow::onOpenAudioFileClicked()
{
    const QString FilePath = QFileDialog::getOpenFileName(nullptr,
                                                    tr("Select Audio File"),
                                                    QDir::homePath(),
                                                    "Audio Files (*.mp3 *.wav *.flac);;All Files (*.*)");

    if (!FilePath.isEmpty())
    {
        emit audioFileSelected(FilePath);
    }
}
