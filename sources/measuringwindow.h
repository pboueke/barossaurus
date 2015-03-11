#ifndef MEASURINGWINDOW_H
#define MEASURINGWINDOW_H

#include <QMainWindow>
#include <cv.h>
#include <highgui.h>
#include "camera.h"
#include <QMessageBox>
#include "linemarker.h"
#include "linemarkercontrols.h"

namespace Ui {
class MeasuringWindow;
}

class MeasuringWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MeasuringWindow(int camIndex, QWidget *parent = 0);
    ~MeasuringWindow();
    void setLineMarker(LineMarker mytarget);
    void setCamera(Camera thisCamera);


private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MeasuringWindow *ui;
};

#endif // MEASURINGWINDOW_H
