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
        formatLabel->setMaximumSize(QSize(70,  35));

        fileNameLabel->setMinimumSize(90,25);
        lengthLabel  ->setMinimumSize(80,25);
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
    void configureLabel(int row, PlayListItem *item, QAbstractItemDelegate *delegate, bool show);
    QAbstractItemDelegate *defaultDelegate() const;
    int labelRow() const;
    void hideLabel();
    bool draggingMode()const;
private:
    DragLabelItemInfo itemInfo;
    int _Row = -1;
    bool _DraggingMode = false;
    QHBoxLayout  *horizontalLayout          = nullptr;
    QAbstractItemDelegate *_DefaultDelegate  = nullptr;
    PlayListItem *_Labelitems = nullptr;

    //Methods
    void setProperties();

    void setDefaultDelegate(QAbstractItemDelegate *item);
    void setLabelItems(PlayListItem *item);
    void setLabelRow(int row);

    void setDraggingMode(bool mode);
    void showLabel();
public slots:
    void updateLabelPosition(int x , int y);
    void mouseReleased();
};

#endif // DRAGHANDLER_H
