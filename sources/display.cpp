#include "display.h"
#include "ui_display.h"
#include <QLabel>
#include <QPixmap>

Display::Display(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);
}

Display::~Display()
{
    delete ui;
}
