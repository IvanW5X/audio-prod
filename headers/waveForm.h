/**********************************************************
 * Description: Header file for the wave form widget.
 * Computes and draws the wave form of an audio file
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QWidget>

namespace Ui
{
    class WaveForm;
}

class WaveForm : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and Destructor
        explicit WaveForm(QWidget *parent = nullptr);
        ~WaveForm();

        // Public APIs
        void init();

    private:
        Ui::WaveForm *ui;
};
