#include "tabledelegate.h"
#include <QApplication>

void TableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
   if (index.column() == 3) {
       int state = index.model()->data(index, Qt::DisplayRole).toInt();
       QString str_state = "状态未知";
       switch (state) {
       case 0:
           str_state = "等待签名";
           break;
       case 1:
           str_state = "签名中";
           break;
       case 2:
           str_state = "签名成功";
           break;
       case 3:
           str_state = "签名失败";
           break;
        default:
           break;
       }
       QApplication::style()->drawItemText(painter, option.rect.adjusted(40,0,0,0), option.displayAlignment, QApplication::palette(), true, str_state);
   } else {
       return QItemDelegate::paint(painter, option, index);
   }
}
