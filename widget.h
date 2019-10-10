#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "expression.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:
    void ReadExpr();
    void WriteExpr();
    void Assign();
    int Value();
    void CompoundExpr();
    void MergeConst();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
