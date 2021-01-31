#include "iqplayer.h"
#include "ui_iqplayer.h"
#include <QDebug>
#include <QCloseEvent>
#include <QSharedPointer>


IQPlayer::IQPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::IQPlayer)
{
    ui->setupUi(this);
    setupMainUi();
    setProperties();
    setupPlots();
    setupConnections();
//    tryPlot();

}

IQPlayer::~IQPlayer()
{
    delete ui;
}

void IQPlayer::setProperties()
{
    this->setProperty("class","mainWidget");
}

void IQPlayer::setupConnections()
{
    connect(playListView,&PlayListView::playingItemListRequested,       player      ,&VoicePlayer::requestToPlay);
    connect(this        ,&IQPlayer::windowSizeChanged,                  playListView,&PlayListView::onResizingViewList);
    connect(fftGroupBox ,&FFTGroupBox::openFilesRequested,              playListView,&PlayListView::onOpenFiles);
    connect(plot1       ,&QCustomPlot::mouseDoubleClick,                this,&IQPlayer::plot1RescaleRequested);
    connect(plot2       ,&QCustomPlot::mouseDoubleClick,                this,&IQPlayer::plot2RescaleRequested);
    connect(action      ,&QAction::toggled,                             this,&IQPlayer::onWindowsState);
    connect(player      ,&VoicePlayer::played,                          this,&IQPlayer::playerPlayed);
    connect(player      ,&VoicePlayer::paused,                          this,&IQPlayer::playerPaused);
    connect(player      ,&VoicePlayer::stopped,                         this,&IQPlayer::playerStopped);
    connect(player      ,&VoicePlayer::verticalRescaleRequested,        this,&IQPlayer::playerRescaledVertically);
    connect(player      ,&VoicePlayer::horizontalRescaleRequested,      this,&IQPlayer::playerRescaledHorizontally);
    connect(player      ,&VoicePlayer::playNextRequested,               this,&IQPlayer::playerNextRequested);
    connect(player      ,&VoicePlayer::playPreviousRequested,           this,&IQPlayer::playerPreviousRequested);
    connect(player      ,&VoicePlayer::repeatModeChanged,               this,&IQPlayer::playerRepeatStateChanged);
    connect(ddcGroupBox ,&DDCGroupBox::spanCenterChanged,               this,&IQPlayer::spanCenterChanged);
    connect(ddcGroupBox ,&DDCGroupBox::ddcCenterChanged,                this,&IQPlayer::ddcCenterChanged);
    connect(ddcGroupBox ,&DDCGroupBox::demodGainChanged,                this,&IQPlayer::demodGainChanged);
    connect(ddcGroupBox ,&DDCGroupBox::demodulationTypeChanged,         this,&IQPlayer::demodulationTypeChanged);
    connect(ddcGroupBox ,&DDCGroupBox::bandWidthFrequencyChanged,       this,&IQPlayer::bandWidthFrequencyChanged);
    connect(fftGroupBox ,&FFTGroupBox::averageChanged,                  this,&IQPlayer::averageChanged      );
    connect(fftGroupBox ,&FFTGroupBox::nfftChanged,                     this,&IQPlayer::nfftChanged         );
    connect(fftGroupBox ,&FFTGroupBox::playFrequencyChanged,            this,&IQPlayer::playFrequencyChanged);
    connect(fftGroupBox ,&FFTGroupBox::windowTypeChanged,               this,&IQPlayer::windowTypeChanged   );
}

void IQPlayer::setupPlots()
{
    QLinearGradient gradient(0,0,0,400);
    gradient.setColorAt(0,QColor(150,150,150));
    gradient.setColorAt(0.38,QColor(180,180,180));
    gradient.setColorAt(1,QColor(190,190,190));

    plot1 = new QCustomPlot(plotWidget1);
    plot2 = new QCustomPlot(plotWidget2);

    plot1->setBackground(QColor(100,100,100));
    plot2->setBackground(QColor(100,100,100));

    plotLayout1->addWidget(plot1);
    plotLayout2->addWidget(plot2);
}

void IQPlayer::setupMainUi()
{
    ddcGroupBox    = new DDCGroupBox        (this);
    fftGroupBox    = new FFTGroupBox        (this);
    infoGroupBox   = new InformationGroupBox(this);
    player         = new VoicePlayer        (this);

    this->setWindowState(Qt::WindowMaximized);
    mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(9);

    leftWidget = new QWidget(this);
    playListView = new PlayListView(this);


    mainLayout->addWidget(leftWidget);
    mainLayout->addWidget(playListView);

    leftWidget->setMinimumWidth(700);
    leftLayout = new QVBoxLayout(leftWidget);

    plotWidget1 = new QWidget(leftWidget);
    plotWidget1->setMinimumHeight(200);

    plotLayout1 = new QGridLayout(plotWidget1);

    plotWidget2 = new QWidget(leftWidget);
    plotWidget2->setMinimumHeight(200);

    plotLayout2 = new QGridLayout(plotWidget2);

    leftLayout->addWidget(plotWidget1,1);
    leftLayout->addWidget(plotWidget2,1);

    innerWidget = new QWidget(leftWidget);
    leftLayout->addWidget(innerWidget);
    leftLayout->setMargin(5);

    innerLeftHLayout = new QHBoxLayout(innerWidget);
    innerLeftHLayout->addWidget(ddcGroupBox);
    innerLeftHLayout->addWidget(fftGroupBox);
    innerLeftHLayout->addWidget(infoGroupBox);

    innerLeftHLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
    leftLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);

    leftLayout->addWidget(player);

    player->timeLine()->setTracking(false);
    player->timeLine()->setTabletTracking(true);

    action = new QAction(this);
    action->setCheckable(true);
    action->setShortcut(QKeySequence(Qt::Key::Key_F11));
    this->addAction(action);


}

void IQPlayer::tryPlot()
{

    ////////////////////////////PLOT2///////////////////////////////

    QVector<double> bardata,bardata2,tick;
    QCPBars * bar = new QCPBars(plot2->xAxis,plot2->yAxis);
    QCPBars * bar2 = new QCPBars(plot2->xAxis,plot2->yAxis);
    QVector <QString> labels;QVector<double>ticks;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

    tick << 0 << 1 << 2 << 3 << 4 << 5<<6<<7<<8<<9<<10;
    bardata << 4 << 5 << 8 << 4 << 3<<6<<1<<2<<9<<7<<4;
    bardata2 << 4<<1<<0.5<<1<<3<<2<<3<<2<<0.5<<1<<2;

    bar->setData(tick,bardata);
    bar2->setData(tick,bardata2);
    bar2->moveAbove(bar);


    bar->setAntialiased(false);
    bar2->setAntialiased(false);

    bar->setPen(QPen(QColor(111,9,176).lighter(170)));
    bar->setBrush(QColor(111,9,176));
    bar2->setBrush(QColor(250,170,20));
    bar2->setPen(QPen(QColor(250,170,20).lighter(150)));
    plot2->xAxis->setRange(-0.5,10.5);
    plot2->yAxis->setRange(0,12.5);
    plot2->yAxis->setSubTicks(false);
    labels << "Iran"<<"Spain"<<"France"<<"England"<<"USA"<<"Germany"<<"Finland"<<"Italia"<<"Brazil"<<"China"<<"Russia";
    ticks<<0<<1<<2<<3<<4<<5<<6<<7<<8<<9<<10;
    textTicker->addTicks(ticks,labels);
    plot2->xAxis->setTicker(textTicker);
    plot2->xAxis->setLabel("Countries");
    plot2->yAxis->setLabel("Data");

    ////////////////////////////PLOT1///////////////////////////////

    QCPStatisticalBox * statistical = new QCPStatisticalBox(plot1->xAxis,plot1->yAxis);
    QSharedPointer<QCPAxisTickerText> textTicker1(new QCPAxisTickerText);

    QCPItemText *textLabel = new QCPItemText(plot1);
    textLabel->setPositionAlignment(Qt::AlignTop | Qt::AlignCenter);
    textLabel->position->setCoords(2,6.8);
    textLabel->setText("This is text and looks funny");
    textLabel->setPadding(QMargins(3,3,3,3));
    textLabel->setPen(QPen(Qt::black));

    QCPItemLine *arrow = new QCPItemLine(plot1);
    arrow->start->setParentAnchor(textLabel->bottom);
    arrow->end->setCoords(1,3);
    arrow->setHead(QCPLineEnding::esSpikeArrow);

    textTicker1->addTick(1,"sample1");
    textTicker1->addTick(2,"sample2");
    plot1->xAxis->setTicker(textTicker1);
    plot1->rescaleAxes();

    statistical->addData(1,1.1,1.9,2.25,2.7,4.2);
    statistical->addData(2,0.8,1.6,2.2,3.2,4.9,QVector<double>()<<0.7<<0.34<<6.0);
    plot1->xAxis->setSubTicks(false);
    plot1->xAxis->setTickLength(0,4);
    plot1->xAxis->setTickLabelRotation(20);
    plot1->xAxis->scaleRange(1.7,plot1->xAxis->range().center());
    plot1->yAxis->setRange(0,7);
    plot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    plot1->replot();

    ////////////////////////////////////////////////////////////////
}

void IQPlayer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit windowSizeChanged();
}

void IQPlayer::onWindowsState()
{
    if(action->isChecked()){
        this->setWindowState(Qt::WindowFullScreen);
    }
    else{
        this->setWindowState(Qt::WindowMaximized);
    }
}

void IQPlayer::closeEvent(QCloseEvent *event)
{
    msgBox = new QMessageBox(this);
    msgBox->setWindowFlag(Qt::FramelessWindowHint);
    msgBox->setIcon(QMessageBox::Question);
    msgBox->setText("Are you sure to exit the program ?");
    msgBox->setStandardButtons(QMessageBox::No | QMessageBox::Yes);
    msgBox->setDefaultButton(QMessageBox::No);
    int ret = msgBox->exec();
    msgBox->close();
    if(ret == QMessageBox::Yes){
        event->accept();
        qApp->closeAllWindows();
    }else if(ret == QMessageBox::No){
        event->ignore();
    }
    msgBox->deleteLater();
}

