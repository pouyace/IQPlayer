#include "informationgroupbox.h"
#include "ui_informationgroupbox.h"

InformationGroupBox::InformationGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::InformationGroupBox)
{
    ui->setupUi(this);
    ui->RecordingTimeFixedLabel->setProperty("class","FixedLabels");
    ui->SNRFixedLabel->setProperty("class","FixedLabels");
    ui->CenterFrequencyFixedLabel->setProperty("class","FixedLabels");
    ui->recordingTimeLabel->setProperty("class","InfoLabel");
    ui->SNRLabel->setProperty("class","InfoLabel");
    ui->centerFrequencyLabel->setProperty("class","InfoLabel");
}

InformationGroupBox::~InformationGroupBox()
{
    delete ui;
}

void InformationGroupBox::setRecordingTime(QString time)
{
    ui->recordingTimeLabel->setText(time);
}

void InformationGroupBox::setCenterFrequency(qint64 frequency)
{
    ui->centerFrequencyLabel->setNum(int(frequency));
}

void InformationGroupBox::setSNR(double snr)
{
    ui->SNRLabel->setNum(snr);
}
