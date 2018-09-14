#pragma once
#include <QMainWindow>

namespace Ui {
class QTExample;
}

class QTExample : public QMainWindow
{
    Q_OBJECT

public:
    explicit QTExample(QWidget *parent = 0);
    ~QTExample();

private:
    Ui::QTExample *ui;
};

