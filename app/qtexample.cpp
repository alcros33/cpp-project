#include "qtexample.h"
#include "ui_qtexample.h"

QTExample::QTExample(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QTExample)
{
    ui->setupUi(this);
}

QTExample::~QTExample()
{
    delete ui;
}
