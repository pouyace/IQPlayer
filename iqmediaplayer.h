#ifndef VOICEPLAYER_H
#define VOICEPLAYER_H
#include <QVBoxLayout>
#include <QWidget>
#include <QSlider>
namespace Ui {
class VoicePlayer;
}

class VoicePlayer : public QWidget
{
    Q_OBJECT

public:
    explicit VoicePlayer(QWidget *parent = nullptr);
    ~VoicePlayer();
    QSlider *timeLine();
private:
    Ui::VoicePlayer *ui;
    void setupConncetion();
    bool repeatState = 1;
    bool pauseState   = 1;
    bool hasAnythingToPlay = false;
    int currentFileIndex = 0;
    QString currentFilePath = "";

private slots:
    void stop();
    void play();
    void next();
    void previous();

public slots:
    void updateRepeatStat();
    void updatePauseStat();
    void requestToPlay(QString path,int index);

signals:
    void paused();
    void played();
    void stopped();
    void repeatModeChanged();
    void horizontalRescaleRequested();
    void verticalRescaleRequested();
    void playNextRequested(int index);
    void playPreviousRequested(int index);


};

#endif // VOICEPLAYER_H
