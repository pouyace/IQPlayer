#ifndef DDCGROUPBOX_H
#define DDCGROUPBOX_H
#include <barradiobutton.h>
#include <QGroupBox>

namespace Ui {
class DDCGroupBox;
}
class DDCGroupBox : public QGroupBox
{
    Q_OBJECT
    Q_PROPERTY(qint64 spanCenter WRITE setSpanCenter READ spanCenter NOTIFY spanCenterChanged)
    Q_PROPERTY(qint64 ddcCenter WRITE setDDCCenter READ DDCCenter NOTIFY ddcCenterChanged)
    Q_PROPERTY(double demodGain WRITE setDemodGain READ demodGain NOTIFY demodGainChanged)
    Q_PROPERTY(DemodulationType  demodulationType WRITE setDemodulationType READ demodulationType NOTIFY demodulationTypeChanged)
    Q_PROPERTY(qint64 bandWidthFrequency WRITE setBandWidthFrequency READ bandWidthFrequency NOTIFY bandWidthFrequencyChanged)

public:
    enum DemodulationType{AM,FM};
    Q_ENUM(DemodulationType)

    explicit DDCGroupBox(QWidget *parent = nullptr);
    ~DDCGroupBox();
    qint64 spanCenter();
    qint64 DDCCenter();
    qint64 bandWidthFrequency();
    double demodGain();
    DemodulationType demodulationType();
private:
    Ui::DDCGroupBox *ui;
    qint64 _spanCenter;
    qint64 _ddcCenter;
    double _demodGain;
    qint64 _bandWidthFrequency = 1500;
    DemodulationType _demodulationType = FM;
public slots:
    void setSpanCenter              (qint64 spanCenter);
    void setDDCCenter               (qint64 ddcCenter);
    void setDemodGain               (double demodGain);
    void setDemodulationType        (DemodulationType type);
    void setBandWidthFrequency      (qint64 bandWidth);
private slots:
    void onBandwidthValueChange     (QVariant value);
    void onDemodulationValueChanged (QVariant value);
    void onSpanCenterValueChanged   (double   value);
    void onDDCCenterValueChanged    (double   value);
    void onDemodGainValueChanged    (double   value);
    void onExportButtonClicked();
    void onColorButtonClicked();
signals:

    /*******DDC******/
    void spanCenterChanged          (qint64);
    void ddcCenterChanged           (qint64);
    void demodGainChanged           (double);
    void demodulationTypeChanged    (DemodulationType);
    void bandWidthFrequencyChanged  (qint64);
};

#endif // DDCGROUPBOX_H
