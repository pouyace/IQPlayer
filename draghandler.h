#ifndef DRAGHANDLER_H
#define DRAGHANDLER_H
#include <QLabel>
#include <tablemodel.h>
struct DragLabelItemInfo{
    QLabel  *fileNameLabel                  = nullptr;
    QLabel  *lengthLabel                    = nullptr;
    QLabel  *formatLabel                    = nullptr;

    DragLabelItemInfo(QWidget *parent){
        fileNameLabel   = new QLabel(parent);
        lengthLabel     = new QLabel(parent);
        formatLabel     = new QLabel(parent);

        fileNameLabel->setMaximumSize(QSize(90,35));
        lengthLabel->setMaximumSize(QSize(90,  35));
        formatLabel->setMaximumSize(QSize(90,  35));

        fileNameLabel->setMinimumSize(80,25);
        lengthLabel  ->setMinimumSize(60,25);
        formatLabel  ->setMinimumSize(80,25);

        fileNameLabel->setMargin(0);
        lengthLabel->setMargin(0);
        formatLabel->setMargin(0);

        fileNameLabel->setProperty("class","FixedLabels");
    }
};
class DragLabelItem : public QWidget
{
public:
    DragLabelItem(QWidget *parent,QAbstractItemDelegate* itemDelegate = nullptr);
    ~DragLabelItem();
    void setLabelsText(PlayListItem *item);
    void setLabelState(bool state);
    void setDefaultDelegate(QAbstractItemDelegate *item);
    QAbstractItemDelegate *defaultDelegate() const;
    void setIndex(int row);
    int row() const;
private:
    int _row;
    DragLabelItemInfo itemInfo;
    QHBoxLayout  *horizontalLayout          = nullptr;
    QAbstractItemDelegate *_defaultDelegate  = nullptr;

    //Methods
    void setProperties();
public slots:
    void updateLabelPosition(int x , int y);
    void mouseReleased();
};

#endif // DRAGHANDLER_H
