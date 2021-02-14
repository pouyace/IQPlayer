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

        fileNameLabel->setMinimumSize(20,25);
        lengthLabel  ->setMinimumSize(20,25);
        formatLabel  ->setMinimumSize(20,25);

        fileNameLabel->setMargin(0);
        lengthLabel->setMargin(0);
        formatLabel->setMargin(0);

        lengthLabel->setAlignment(Qt::AlignCenter);

        fileNameLabel->setProperty("class","FixedLabels");


        fileNameLabel->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
        lengthLabel  ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
        formatLabel  ->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
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
    void hideLabel();
    void setDraggingMode(bool mode);
    void showLabel();
public slots:
    void updateLabelPosition(int x , int y);
    void mouseReleased();
    void onSetLabelSize(const QSize& size);
};

#endif // DRAGHANDLER_H
