#include "fftgroupbox.h"
#include "ui_fftgroupbox.h"
#include <QMetaEnum>
#include <standardwindowcofactor.h>
#include <QDebug>
#include <QFileDialog>
//#include "AMRComplex/amrdetails.h"
FFTGroupBox::FFTGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::FFTGroupBox)
{
    ui->setupUi(this);
    ui->playFrequencyComboBox->addItem("50 Hz",50);
    ui->playFrequencyComboBox->addItem("20 Hz",20);
    ui->playFrequencyComboBox->addItem("10 Hz",10);
    ui->playFrequencyComboBox->addItem("5 Hz",5);
    ui->playFrequencyComboBox->addItem("1 Hz",1);
    ui->playFrequencyComboBox->setCurrentIndex(3);

    for(int i=9; i<15; i++){
        quint64 mNFFT = 1 << i;
        ui->NFFTComboBox->addItem(QString::number(mNFFT),mNFFT);
    }

    registerWindowMethod(Blackman_Symmetric         ,&StandardWindowCoFactor::Blackman::generateSymmetric        );
    registerWindowMethod(Blackman_Periodic          ,&StandardWindowCoFactor::Blackman::generatePeriodic         );
    registerWindowMethod(Blackman__Harris_Symmetric ,&StandardWindowCoFactor::BlackmanHarris::generateSymmetric  );
    registerWindowMethod(Blackman__Harris_Periodic  ,&StandardWindowCoFactor::BlackmanHarris::generatePeriodic   );

    ui->NFFTFixedLabel->setProperty             ("class","FixedLabels");
    ui->averageFixedLabel->setProperty          ("class","FixedLabels");
    ui->windowsTypeFixedLabel->setProperty      ("class","FixedLabels");
    ui->playFrequencyFixedLabel->setProperty    ("class","FixedLabels");

    connect(ui->averageSpinBox,         QOverload<int>::of(&QSpinBox::valueChanged)         ,this,&FFTGroupBox::onAverageChanged);
    connect(ui->playFrequencyComboBox,  QOverload<int>::of(&QComboBox::currentIndexChanged) ,this,&FFTGroupBox::onPlayFrequencyChanged);
    connect(ui->NFFTComboBox,           QOverload<int>::of(&QComboBox::currentIndexChanged) ,this,&FFTGroupBox::onNFFTChanged);
    connect(ui->windowsTypeComboBox,    &QComboBox::currentTextChanged                      ,this,&FFTGroupBox::onWindowTypeChanged);
    connect(ui->doAMRPushButton,        &QPushButton::clicked                               ,this,&FFTGroupBox::onDoAMRButtonClicked);
    connect(ui->openFilesPushButton,    &QPushButton::clicked                               ,this,&FFTGroupBox::onOpenFilesButtonClicked);
    connect(ui->fullSpanPushButton,     &QCheckBox::stateChanged                            ,this,&FFTGroupBox::onFullSpanStateChanged);
    //onAverageChanged(1);
    //amrDetails = new AMRDetails(this);
}

FFTGroupBox::~FFTGroupBox()
{
    delete ui;
}

int FFTGroupBox::average()
{
    return this->_average;
}

int FFTGroupBox::playFrequency()
{
    return this->_playFrequency;
}

int FFTGroupBox::NFFT()
{
    return this->_NFFT;
}

FFTGroupBox::WindowType FFTGroupBox::windowType()
{
    return this->_windowType;
}

void FFTGroupBox::registerWindowMethod(FFTGroupBox::WindowType winType, FFTGroupBox::WindowMethod winMethod)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<WindowType>();
    QString name(metaEnum.valueToKey(winType));
    name = name.replace("__","-");
    name = name.replace("_"," ");
    ui->windowsTypeComboBox->addItem(name,QVariant::fromValue<void*>((void*)winMethod));
}

void FFTGroupBox::onWindowTypeChanged(QString type)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<WindowType>();
    type = type.replace(" ", "_");
    type = type.replace("-","__");
    _windowType =WindowType(metaEnum.keyToValue(type.toStdString().c_str()));
    qDebug()<<"WindowType="<<_windowType;
     _winMethod =  WindowMethod(ui->windowsTypeComboBox->currentData().value<void*>());
    qDebug()<<"winMethod="<<_winMethod;
    emit windowTypeChanged();
}

void FFTGroupBox::onAverageChanged(int average)
{
    this->_average = ui->averageSpinBox->value();
    qDebug()<<"average:"<<_average;
    emit averageChanged(_average);
}

void FFTGroupBox::onOpenFilesButtonClicked()
{
    QStringList files = QFileDialog::getOpenFileNames(this,"select files to play");
    emit openFilesRequested(files);
}

void FFTGroupBox::onDoAMRButtonClicked()
{
    qDebug()<<"Do AMR";
    if(amrDetails){
        //amrDetails->show();
        //amrDetails->raise();
    }
}

void FFTGroupBox::onFullSpanStateChanged(bool state)
{
    qDebug()<<"Full Span";
}

void FFTGroupBox::onNFFTChanged(int)
{
    this->_NFFT = ui->NFFTComboBox->currentData().toInt();
    qDebug()<<"NFFT:"<<_NFFT;
    emit nfftChanged(_NFFT);
}

void FFTGroupBox::onPlayFrequencyChanged(int)
{
    this->_playFrequency = ui->playFrequencyComboBox->currentData().toInt();
    qDebug()<<"playFrequency:"<<_playFrequency;
    emit playFrequencyChanged(_playFrequency);
}
