#ifndef INFORMATIONGROUPBOX_H
#define INFORMATIONGROUPBOX_H

#include <QGroupBox>

namespace Ui {
class InformationGroupBox;
}

class InformationGroupBox : public QGroupBox
{
    Q_OBJECT

public:
    explicit InformationGroupBox(QWidget *parent = nullptr);
    ~InformationGroupBox();
public slots:
    void setRecordingTime(QString time);
    void setCenterFrequency(qint64 frequency);
    void setSNR(double snr);
private:
    Ui::InformationGroupBox *ui;
};

#endif // INFORMATIONGROUPBOX_H
