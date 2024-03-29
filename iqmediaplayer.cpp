#include "iqmediaplayer.h"
#include "ui_iqmediaplayer.h"
#include <QDebug>
#include <QTimer>
#include <QFileInfo>
VoicePlayer::VoicePlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VoicePlayer)
{
    ui->setupUi(this);
    ui->playToolButton->setChecked(!pauseState);
    ui->repeatToolButton->setChecked(!repeatState);
    setupConncetion();
}

VoicePlayer::~VoicePlayer()
{
    delete ui;
}

QSlider* VoicePlayer::timeLine()
{
    return ui->horizontalSlider;
}

void VoicePlayer::setupConncetion()
{
    connect(ui->nextToolButton,                 &QToolButton::clicked,  this,&VoicePlayer::next);
    connect(ui->previousToolButton,             &QToolButton::clicked,  this,[=]{emit playPreviousRequested(currentFileIndex -1);});
//    connect(ui->rescaleVerticallyToolButton,    &QToolButton::clicked,  this,   &VoicePlayer::verticalRescaleRequested);
//    connect(ui->rescaleHorizontallyToolButton,  &QToolButton::clicked,  this,   &VoicePlayer::horizontalRescaleRequested);
    connect(ui->stopToolButton,                 &QToolButton::clicked,  this,   &VoicePlayer::stop);
    connect(ui->playToolButton,                 &QToolButton::clicked,  this,   &VoicePlayer::play);
//    connect(ui->repeatToolButton,               &QToolButton::clicked,  this,   &VoicePlayer::updateRepeatStat);
}

void VoicePlayer::stop()
{

}

void VoicePlayer::play()
{
    QFileInfo fileInfo(currentFilePath);
    if(fileInfo.isReadable()){

    }
}

void VoicePlayer::next()
{
    stop();
    emit playNextRequested(currentFileIndex + 1);
}

void VoicePlayer::previous()
{
    stop();
    emit playPreviousRequested(currentFileIndex - 1);
}

void VoicePlayer::updateRepeatStat()
{
    bool newRepeatState = ui->repeatToolButton->isChecked() ? 0 : 1;
    if(newRepeatState != repeatState){
        qDebug()<<"repeat state changed";
        repeatState = newRepeatState;
        emit repeatModeChanged();
    }
}

void VoicePlayer::updatePauseStat()
{
    bool newPauseState = ui->playToolButton->isChecked()  ? 0 : 1;
    if(pauseState != newPauseState){
        pauseState  = newPauseState;
        if(pauseState){
            qDebug()<<"paused";
            emit paused();
        }
        else{
            qDebug()<<"played";
            emit played();
        }
    }
}

void VoicePlayer::requestToPlay(QString path, int index)
{
    currentFilePath = path;
    this->stop();
}
