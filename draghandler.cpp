#include "draghandler.h"
#include <QMouseEvent>
DragLabelItem::DragLabelItem(QWidget *parent, QAbstractItemDelegate *itemDelegate):
    QWidget(parent),
    itemInfo(this),
    _DefaultDelegate(itemDelegate)
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

void DragLabelItem::setLabelItems(PlayListItem *item)
{
    if(!item)
        return;
    itemInfo.formatLabel    ->setText(item->format);
    itemInfo.lengthLabel    ->setNum(item->lenght);
    itemInfo.fileNameLabel  ->setText(item->absoluteFileName());
}

void DragLabelItem::configureLabel(int row, PlayListItem* item, QAbstractItemDelegate *delegate, bool show)
{
    this->setLabelItems(item);
    this->setDefaultDelegate(delegate);
    this->setLabelRow(row);
    setDraggingMode(show);
    if(show)
        this->showLabel();
    else
        this->hideLabel();
}

void DragLabelItem::hideLabel()
{
    this->hide();
}

bool DragLabelItem::draggingMode() const
{
    return _DraggingMode;
}

void DragLabelItem::setDefaultDelegate(QAbstractItemDelegate *item)
{
    this->_DefaultDelegate = item;
}

QAbstractItemDelegate* DragLabelItem::defaultDelegate() const
{
    return _DefaultDelegate;
}

void DragLabelItem::setLabelRow(int row)
{
    _Row = row;
}

int DragLabelItem::labelRow() const
{
    return _Row;
}

void DragLabelItem::setDraggingMode(bool state)
{
    this->_DraggingMode = state;
}

void DragLabelItem::showLabel()
{
    this->show();
    this->raise();
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
    setDraggingMode(false);
    this->hideLabel();

}
