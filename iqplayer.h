#ifndef IQPLAYER_H
#define IQPLAYER_H

#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <qcustomplot.h>
#include <QMessageBox>
#include <QGridLayout>
#include <barradiobutton.h>
#include "ddcgroupbox.h"
#include "tablemodel.h"
#include "fftgroupbox.h"
#include "iqmediaplayer.h"
#include "playlistview.h"
#include "informationgroupbox.h"
QT_BEGIN_NAMESPACE
namespace Ui { class IQPlayer; }
QT_END_NAMESPACE

class IQPlayer : public QWidget
{
    Q_OBJECT

public:
    IQPlayer(QWidget *parent = nullptr);
    ~IQPlayer();
private:
    Ui::IQPlayer         *ui;
    QHBoxLayout          *mainLayout       = nullptr;
    QWidget              *innerWidget      = nullptr;
    QWidget              *leftWidget       = nullptr;
    QVBoxLayout          *leftLayout       = nullptr;
    QHBoxLayout          *innerLeftHLayout = nullptr;
    QWidget              *plotWidget1      = nullptr;
    QWidget              *plotWidget2      = nullptr;
    QMessageBox          *msgBox           = nullptr;
    QCustomPlot          *plot1            = nullptr;
    QCustomPlot          *plot2            = nullptr;
    QLayout              *plotLayout1      = nullptr;
    QLayout              *plotLayout2      = nullptr;
    DDCGroupBox          *ddcGroupBox      = nullptr;
    FFTGroupBox          *fftGroupBox      = nullptr;
    InformationGroupBox  *infoGroupBox     = nullptr;
    VoicePlayer          *player           = nullptr;
    QAction              *action           = nullptr;
    PlayListView         *playListView     = nullptr;

    void setupMainUi();
    void tryPlot();
    void setProperties();
    void setupConnections();
    void setupPlots();
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onWindowsState();

signals:
    void windowSizeChanged();
    void plot1RescaleRequested();
    void plot2RescaleRequested();
    void playerPaused();
    void playerPlayed();
    void playerStopped();
    void playerRescaledHorizontally();
    void playerRescaledVertically();
    void playerRepeatStateChanged();
    void playerNextRequested();
    void playerPreviousRequested();
    void spanCenterChanged          (qint64);
    void ddcCenterChanged           (qint64);
    void demodGainChanged           (double);
    void demodulationTypeChanged    (DDCGroupBox::DemodulationType);
    void bandWidthFrequencyChanged  (qint64);
    void averageChanged(int average);
    void nfftChanged(int NFFT);
    void playFrequencyChanged(int playFrequency);
    void windowTypeChanged();

};
#endif // IQPLAYER_H
