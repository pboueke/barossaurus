#include "linemarkercontrols.h"
#include "ui_linemarkercontrols.h"
#include <cv.h>
#include <highgui.h>
#include <QMessageBox>
#include "linemarker.h"

LineMarker *target;

lineMarkerControls::lineMarkerControls(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lineMarkerControls)
{
    ui->setupUi(this);
}

lineMarkerControls::~lineMarkerControls()
{
    delete ui;
}

void lineMarkerControls::setTarget(LineMarker *mytarget){
    target = mytarget;
}

void lineMarkerControls::on_topSelect_clicked()
{
    target->chooseLine(true);
}

void lineMarkerControls::on_bottomSelect_clicked()
{
    target->chooseLine(false);
}

void lineMarkerControls::on_doneButton_clicked()
{
    //cv::destroyWindow("Line marker");//fix later: this piece of code depends on the lineMarkerName string on LineMarker class
    target->stopMarking();
    QMessageBox msgBox;
    msgBox.setText("Line marking stopped. To close linemarking, press any key with the linemarking window selected.");
    msgBox.exec();
    cv::destroyWindow("Line marker");//fix later: this piece of code depends on the lineMarkerName string on LineMarker class
        target->stopMarking();
    this->close();
}
