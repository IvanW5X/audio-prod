/**********************************************************
 * Description: Implementation file for the audio data widget
 * 
 * Date: 2025-09-28
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "audioDataWidget.h"
#include "ui_audioDataWidget.h"

// Constructor
AudioDataWidget::AudioDataWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioDataWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

AudioDataWidget::~AudioDataWidget()
{
    delete ui;
}

void AudioDataWidget::init()
{
    // TODO: init the data to default values
}