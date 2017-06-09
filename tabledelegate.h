#ifndef TABLEDELEGATE_H
#define TABLEDELEGATE_H
#include <QItemDelegate>


class TableDelegate : public QItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // TABLEDELEGATE_H
