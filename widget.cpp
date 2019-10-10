#include "widget.h"
#include "ui_widget.h"
#include<QPushButton>
#include "expression.h"
#include<iostream>
#include<fstream>

binarytree expr;
string str;
bool FLAG = 0;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->readExpr, SIGNAL(clicked(bool)), this, SLOT(ReadExpr()));
    connect(ui->getExpr, SIGNAL(clicked(bool)), this, SLOT(WriteExpr()));
    connect(ui->assign, SIGNAL(clicked(bool)), this, SLOT(Assign()));
    connect(ui->combine, SIGNAL(clicked(bool)), this, SLOT(CompoundExpr()));
    connect(ui->getvalue, SIGNAL(clicked(bool)), this, SLOT(Value()));
    connect(ui->mergeConst, SIGNAL(clicked(bool)), this, SLOT(MergeConst()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::ReadExpr()
{
//    while (!FLAG)
//    {
//        cout << "请输入前缀表达式：";
//        cin >> str;
        QString STR=ui->readexpr->text();
        str = STR.toStdString();
        FLAG = expr.ReadExptr(str);
        if (FLAG)
        {
//            cout << "输入的前缀表达式为：";
            expr.preorder_output();

            ifstream in("preorder.txt");
            string exp;
            in >> exp;
            QString EXP=QString::fromStdString(str);
            ui->outputExpr->setText(EXP);
        }
        else
        {
//            cout << "请重新输入！";
//            break;
//        }
    }
}

void Widget::WriteExpr()
{
    if (FLAG)//已构造
    {
        expr.WriteExpr();
    }
    else
    {
        cout << "请先输入表达式！" << endl;
    }
}

void Widget::Assign()
{
    if (FLAG)//已构造
    {
        cout << "请依次输入要赋值的变量的个数：";
        int num; cin >> num;
        cout << "请依次输入要赋值的变量以及对应要赋的值：" << endl;
        for (int i = 0; i < num; i++)
        {
            char c; int val;
            cin >> c >> val;
            expr.Assign(c, val);
        }
        cout << "赋值后的表达式为：";
        expr.WriteExpr();
    }
    else
    {
        cout << "请先输入表达式！" << endl;
    }
}

int Widget::Value()
{
    if (FLAG)//已构造
    {
        expr.Value_output();
    }
    else
    {
        cout << "请先输入表达式！" << endl;
    }
}

void Widget::CompoundExpr()
{
    cout << "请输入两个新的表达式以及运算符号：";
    string s1, s2; cin >> s1 >> s2;
    char op; cin >> op;
    binarytree ss1, ss2;
    ss1.ReadExptr(s1); ss2.ReadExptr(s2);
    expr.CompoundExpr(op, ss1, ss2);
}


void Widget::MergeConst()
{
    if (FLAG)//已构造
    {
        expr.MergeConst();
    }
    else
    {
        cout << "请先输入表达式！" << endl;
    }
}
