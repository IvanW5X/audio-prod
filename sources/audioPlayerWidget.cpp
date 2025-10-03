/**********************************************************
 * Description: Implementation file for the audio player widget
 * 
 * Date: 2025-09-23
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioPlayerWidget.h"
#include "ui_audioPlayerWidget.h"

// Constructor, initializes UI
AudioPlayerWidget::AudioPlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioPlayerWidget),
    currentFile(QString())
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor, frees memory
AudioPlayerWidget::~AudioPlayerWidget()
{
    delete ui;
}

// Initializes the audio player
void AudioPlayerWidget::init()
{

}
