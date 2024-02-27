#include "mylabel.h"
#include <QAction>
#include <QMenu>
#include <QMouseEvent>
myLabel::myLabel(int NO_)
{
    labelNO_ = NO_;
    this->setAttribute(Qt::WA_Hover, true);
}

bool myLabel::event(QEvent* e)
{
    if (e->type() == QEvent::Enter && flag == 0) // 鼠标光标移入
    {
        setStyleSheet("QLabel { border: 4px solid blue; }");
    } else if (e->type() == QEvent::Leave && flag == 0) // 鼠标光标移出
    {
        setStyleSheet("");
    }
    return QLabel::event(e);
}
void myLabel::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        if (flag == 1) {
            flag = 0;
            setStyleSheet(" ");
        } else if (flag == 0) {
            flag = 1;
            setStyleSheet("QLabel { border: 4px solid blue; }");
        }
    } else if (event->button() == Qt::RightButton) {
        QMenu menu(this);
        QAction* actDelete = menu.addAction("Delete");
        connect(actDelete, &QAction::triggered, this, &myLabel::deleteSlot);
        menu.exec(event->globalPosition().toPoint());
    }
}

void myLabel::deleteSlot()
{
    qDebug() << "deleteSlot";
    emit actDeleteLabel(labelNO_);
}
