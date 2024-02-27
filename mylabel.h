#ifndef MYLABEL_H
#define MYLABEL_H

#include <QEvent>
#include <QLabel>
#include <atomic>
class myLabel : public QLabel {
    Q_OBJECT
public:
    myLabel(int No_);
    bool event(QEvent* e);

public:
    std::atomic<int> flag = 0;

private:
    int labelNO_;

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void actDeleteLabel(int No_);

private slots:
    void deleteSlot();
};

#endif // MYLABEL_H
