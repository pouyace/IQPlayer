#include "ddcgroupbox.h"
#include "ui_ddcgroupbox.h"
#include <QMetaEnum>
#include <QDebug>
DDCGroupBox::DDCGroupBox(QWidget *parent) :
    QGroupBox(parent),
    ui(new Ui::DDCGroupBox)
{
    ui->setupUi(this);
    ui->DemodGainDoubleSpinBox->setValue(0.1);
    ui->DDCCenterFixedLabel->setProperty("class","FixedLabels");
    ui->demodGainFixedLabel->setProperty("class","FixedLabels");
    ui->spanCenterFixedLabel->setProperty("class","FixedLabels");


    QList<QString> fItems;
    QList<QVariant> ddcBandwidths = { 1.5e3  ,2.4e3  ,6e3    ,9e3    ,15e3   ,30e3   ,50e3   ,120e3 };
    fItems<<"1 KHz"<<"2 KHz"<<"6 KHz"<<"9 KHz"<<"15 KHz"<<"30 KHz"<<"50 KHz"<<"120 KHz";
    ui->barRadioButton->setItems(fItems);
    ui->barRadioButton->setItemValues(ddcBandwidths);
    ui->barRadioButton->setChecked(0);

    QList<QString> tItems;
    tItems<<"FM"<<"AM";
    QList<QVariant> tValue = {FM,AM};
    ui->demodulationBarRadioButton->setItems(tItems);
    ui->demodulationBarRadioButton->setItemValues(tValue);
    ui->demodulationBarRadioButton->setChecked(0);
    ui->demodulationBarRadioButton->setButtonsSize(QSize(70,22));

    colorButton = new ColorButton(this);
    colorButton->setColor(QColor(100,100,255));
    colorButton->setMaximumSize(QSize(45,20));
    colorButton->setProperty("class","colorButton");
    ui->horizontalLayout_2->addWidget(colorButton);

    connect(ui->barRadioButton,             &BarRadioButton::currentValueChanged                ,this,&DDCGroupBox::onBandwidthValueChange);
    connect(ui->demodulationBarRadioButton, &BarRadioButton::currentValueChanged                ,this,&DDCGroupBox::onDemodulationValueChanged);
    connect(ui->spanCenterDoubleSpinBox,    QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&DDCGroupBox::onSpanCenterValueChanged);
    connect(ui->DDCCenterDoubleSpinBox,     QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&DDCGroupBox::onDDCCenterValueChanged);
    connect(ui->DemodGainDoubleSpinBox,     QOverload<double>::of(&QDoubleSpinBox::valueChanged),this,&DDCGroupBox::onDemodGainValueChanged);
    connect(colorButton,                    &ColorButton::colorChanged                          ,this,&DDCGroupBox::onColorButtonClicked);
    connect(ui->ExportPushButton,           &QPushButton::clicked                               ,this,&DDCGroupBox::onExportButtonClicked);

    ui->ExportPushButton->setProperty("class","GeneralPushButton");
    colorButton->setProperty("class","ColorWidget");
    qDebug()<<typeid (colorButton).name() ;

}

DDCGroupBox::~DDCGroupBox()
{
    delete ui;
}

qint64 DDCGroupBox::spanCenter()
{
    return _spanCenter;
}

qint64 DDCGroupBox::DDCCenter()
{
    return _ddcCenter;
}

qint64 DDCGroupBox::bandWidthFrequency()
{
    return _bandWidthFrequency;
}

double DDCGroupBox::demodGain()
{
    return _demodGain;
}

DDCGroupBox::DemodulationType DDCGroupBox::demodulationType()
{
    return _demodulationType;
}

void DDCGroupBox::setSpanCenter(qint64 spanCenter)
{
    this->_spanCenter = spanCenter;
    qDebug()<<"spanCenter:"<<_spanCenter;
}

void DDCGroupBox::setDDCCenter(qint64 ddcCenter)
{
    this->_ddcCenter = ddcCenter;
    qDebug()<<"ddcCenter:"<<_ddcCenter;
}

void DDCGroupBox::setDemodGain(double demodGain)
{
    this->_demodGain = demodGain;
    qDebug()<<"demodGain:"<<_demodGain;
}

void DDCGroupBox::setDemodulationType(DemodulationType type)
{
    this->_demodulationType = type;
    qDebug()<<"demodulationType:"<<_demodulationType;
}

void DDCGroupBox::setBandWidthFrequency(qint64 bandWidth)
{
    this->_bandWidthFrequency = bandWidth;
    qDebug()<<"bandWidthFrequency:"<<_bandWidthFrequency;
}

void DDCGroupBox::onBandwidthValueChange(QVariant value)
{
    this->_bandWidthFrequency = value.toULongLong();
    qDebug()<<"bandWidthFrequency:"<<_bandWidthFrequency;
    emit bandWidthFrequencyChanged(_bandWidthFrequency);
}

void DDCGroupBox::onDemodulationValueChanged(QVariant value)
{
    this->_demodulationType = DemodulationType(value.toInt());
    qDebug()<<"demodulationType:"<<_demodulationType;
    emit demodulationTypeChanged(_demodulationType);
}

void DDCGroupBox::onSpanCenterValueChanged(double value)
{
    this->_spanCenter = (value * 1e6);
    qDebug()<<"spanCenter:"<<_spanCenter;
    emit spanCenterChanged(_spanCenter);
}

void DDCGroupBox::onDDCCenterValueChanged(double value)
{
    this->_ddcCenter = (value * 1e6);
    qDebug()<<"ddcCenter:"<<_ddcCenter;
    emit ddcCenterChanged(_ddcCenter);
}

void DDCGroupBox::onDemodGainValueChanged(double value)
{
    this->_demodGain = (value);
    qDebug()<<"demodGain:"<<_demodGain;
    emit demodGainChanged(_demodGain);
}

void DDCGroupBox::onExportButtonClicked()
{
    qDebug()<<"Export";
}

void DDCGroupBox::onColorButtonClicked(QColor color)
{

    colorButton->setColor(color);
}
