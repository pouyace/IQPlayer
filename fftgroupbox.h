#ifndef FFTGROUPBOX_H
#define FFTGROUPBOX_H
#include <QGroupBox>

namespace Ui {
class FFTGroupBox;
}

class FFTGroupBox : public QGroupBox
{
    Q_OBJECT
    Q_PROPERTY(int average READ average WRITE onAverageChanged NOTIFY averageChanged)
    Q_PROPERTY(int playFrequency READ playFrequency WRITE onPlayFrequencyChanged NOTIFY playFrequencyChanged)
    Q_PROPERTY(int NFFT READ NFFT WRITE onNFFTChanged NOTIFY nfftChanged)
public:
    enum WindowType{Blackman_Symmetric,Blackman_Periodic,Blackman__Harris_Symmetric,Blackman__Harris_Periodic};
    Q_ENUM(WindowType)
    typedef QVector<double>(* WindowMethod)(int);

    explicit FFTGroupBox(QWidget *parent = nullptr);
    ~FFTGroupBox();
    int average();
    int playFrequency();
    int NFFT();
    WindowType windowType();
private:
    Ui::FFTGroupBox *ui;
    int _average = -1;
    int _playFrequency = -1;
    int _NFFT = -1;
    WindowType _windowType = Blackman_Symmetric;
    WindowMethod _winMethod = nullptr;

    //Private Methods
    void registerWindowMethod(WindowType winType,WindowMethod winMethod);
private slots:
    void onWindowTypeChanged    (QString type);
    void onPlayFrequencyChanged (int);
    void onNFFTChanged          (int);
    void onAverageChanged       (int average);
    void onOpenFilesButtonClicked();
    void onDoAMRButtonClicked();
    void onFullSpanStateChanged (bool state);
signals:
    /*******FFT******/
    void averageChanged(int average);
    void nfftChanged(int NFFT);
    void playFrequencyChanged(int playFrequency);
    void windowTypeChanged();

};

#endif // FFTGROUPBOX_H
