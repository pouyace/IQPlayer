#include "tableitemdelegate.h"
#include <QDebug>
TableItemDelegate::TableItemDelegate(QObject *parent):
    QItemDelegate(parent)
{

}

void TableItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
//    qDebug()<<Q_FUNC_INFO;
    QStyleOptionViewItem myOption = option;
    QString text = "";
    myOption.text = text;
    myOption.displayAlignment = Qt::AlignCenter;
    this->drawDisplay(painter,myOption,myOption.rect,myOption.text);
}
