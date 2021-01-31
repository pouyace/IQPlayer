#include "draghandler.h"
#include <QMouseEvent>
DragLabelItem::DragLabelItem(QWidget *parent, QAbstractItemDelegate *itemDelegate):
    QWidget(parent),
    itemInfo(this),
    _defaultDelegate(itemDelegate)
{
    horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->addWidget(itemInfo.fileNameLabel);
    horizontalLayout->addWidget(itemInfo.lengthLabel);
    horizontalLayout->addWidget(itemInfo.formatLabel);
    this->setProperties();

}

DragLabelItem::~DragLabelItem()
{

}

void DragLabelItem::setLabelsText(PlayListItem *item)
{
    if(!item)
        return;
    itemInfo.formatLabel    ->setText(item->format);
    itemInfo.lengthLabel    ->setNum(item->lenght);
    itemInfo.fileNameLabel  ->setText(item->absoluteFileName());
}

void DragLabelItem::setLabelState(bool state)
{
    if(!state){
        itemInfo.fileNameLabel->setText("");
        itemInfo.lengthLabel->setNum(-1);
        itemInfo.formatLabel->setText("");
        this->hide();
        return;
    }
    else{
        this->show();
        this->raise();
    }
}

void DragLabelItem::setDefaultDelegate(QAbstractItemDelegate *item)
{
    this->_defaultDelegate = item;
}

QAbstractItemDelegate* DragLabelItem::defaultDelegate() const
{
    return _defaultDelegate;
}

void DragLabelItem::setIndex(int row)
{
    _row = row;
}

int DragLabelItem::row() const
{
    return _row;
}

void DragLabelItem::setProperties()
{
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setWindowFlag(Qt::FramelessWindowHint);
    horizontalLayout->setSizeConstraint(QLayout::SizeConstraint::SetMinAndMaxSize);
    horizontalLayout->setMargin(0);
    this->setMaximumSize(QSize(270,25));
    this->setProperty("class","mainWidget");
}

void DragLabelItem::updateLabelPosition(int x, int y)
{
    this->move(x,y);
}

void DragLabelItem::mouseReleased()
{
    // hide widget and reload removed index
    setLabelState(false);


}
