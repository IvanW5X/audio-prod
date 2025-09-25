/**********************************************************
 * Description: Implementation file for the wave form widget.
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "waveForm.h"
#include "ui_waveForm.h"

// Constructor
WaveForm::WaveForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveForm)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor
WaveForm::~WaveForm()
{
    delete ui;
}

// Initializes the wave form to a default state
void WaveForm::init()
{

}
