/**********************************************************
 * Description: Implementation file for the wave form widget.
 * 
 * Date: 2025-09-24
 * 
 * Author: Ivan Wong
 * 
 **********************************************************/

#include "waveFormWidget.h"
#include "ui_waveFormWidget.h"

// Constructor
WaveFormWidget::WaveFormWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WaveFormWidget),
    audioPlayer(nullptr),
    decoder(new QAudioDecoder(this)),
    audioSamples(std::vector<float_t>(0))
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_StyledBackground);
}

// Destructor
WaveFormWidget::~WaveFormWidget()
{
    delete ui;
}

// Initializes the wave form to a default state
void WaveFormWidget::init(QMediaPlayer *player)
{
    if (!player)
    {
        // TODO: add error handling
        return;
    }
    audioPlayer = player;
}

// Updates the wave form with the new audio file
// Assumes that the file is a valid audio file
void WaveFormWidget::onUpdateWaveForm()
{
    updateAudioSamples();
}

// Gets the data samples from the audio file and stores them into a vector
// Assumes FileName is a valid audio file
void WaveFormWidget::updateAudioSamples()
{
    // QAudioBuffer buffer;
    // QEventLoop loop;

    // decoder->setSource(QUrl::fromLocalFile(FileName));
    // decoder->start();

    // Wait until decoder is done processing audio file
    // (void) connect(decoder, &QAudioDecoder::sourceChanged, [this, &loop]
    // {
    //     const bool IsDoneLoading = decoder->bufferAvailable();

    //     if (IsDoneLoading)
    //     {
    //         printf("trthjkljhgffghjk\n");
    //         fflush(stdout);
    //         loop.quit();
    //     }
    //     printf("trthjkljhgffghjk\n");
    //     fflush(stdout);
    // });
    // loop.exec();
    // // decoder->disconnect();

    // if (decoder->error() != QAudioDecoder::NoError)
    // {
    //     // TODO: error handle
    //     fprintf(stdout, "hgjkl;\n");
    //     fflush(stdout);
    //     return;
    // }
    // buffer = decoder->read();

    // const int32_t SamplesCount = buffer.sampleCount();
    // const float* data = buffer.constData<float>();

    // this->audioSamples.reserve(static_cast<size_t>(SamplesCount));

    // std::copy(data, data + (SamplesCount * sizeof(float)), audioSamples.begin());


    // for (int i = 0 ; i < SamplesCount; i++)
    // {
    //     fprintf(stdout,"%f, ", audioSamples[i]);
    // }
    // fprintf(stdout,"\n%d\n", SamplesCount);
    // fflush(stdout);
}
