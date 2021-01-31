#ifndef TABLEITEMDELEGATE_H
#define TABLEITEMDELEGATE_H
#include <QItemDelegate>

class TableItemDelegate : public QItemDelegate
{
public:
    TableItemDelegate(QObject *parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // TABLEITEMDELEGATE_H
