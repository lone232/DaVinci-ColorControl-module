#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "colorcontrolwidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ColorControlWidget *c = new ColorControlWidget(this);
    // c->setFixedSize(400,600);
    c->show();
    QLabel *lbl_red = new QLabel(this);
    QLabel *lbl_green = new QLabel(this);
    QLabel *lbl_blue = new QLabel(this);
    lbl_red->move(500,100);
    lbl_green->move(500,200);
    lbl_blue->move(500,300);
    lbl_red->setFixedSize(100,30);
    lbl_green->setFixedSize(150,30);
    lbl_blue->setFixedSize(100,30);
    connect(c, &ColorControlWidget::dragPointChange, this, [=]{
        lbl_red->setText(QString("red: %1").arg(c->getOffset().red));
        lbl_green->setText(QString("green: %1").arg(c->getOffset().green));
        lbl_blue->setText(QString("blue: %1").arg(c->getOffset().blue));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
