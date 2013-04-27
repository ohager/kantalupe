#ifndef CLOSEWIDGET_H
#define CLOSEWIDGET_H

#include <QWidget>

class CloseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CloseWidget(QWidget *parent = 0);

signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

private:
    bool mEntered;

};

#endif // CLOSEWIDGET_H
