/**********************************************************
 * Description: Header file for the audio data. Displays the
 * audio player meta data in a human readable form 
 * 
 * Date: 2025-09-28
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#pragma once

#include <QWidget>

namespace Ui
{
    class AudioDataWidget;
}

class AudioDataWidget : public QWidget
{
    Q_OBJECT

    public:
        // Constructor and destructor
        explicit AudioDataWidget(QWidget *parent = nullptr);
        ~AudioDataWidget();

        // Public APIs
        void init();

    signals:

    public slots:

    private slots:

    private:
        // Member variables
        Ui::AudioDataWidget *ui;
};
