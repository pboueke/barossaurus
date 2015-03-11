#ifndef LINEMARKERCONTROLS_H
#define LINEMARKERCONTROLS_H
#include <cv.h>
#include <highgui.h>
#include <QMessageBox>
#include "linemarker.h"
#include <QWidget>

namespace Ui {
class lineMarkerControls;
}

class lineMarkerControls : public QWidget
{
    Q_OBJECT

public:
    explicit lineMarkerControls(QWidget *parent = 0);
    ~lineMarkerControls();
    void setTarget(LineMarker *mytarget);

private slots:
    void on_topSelect_clicked();

    void on_bottomSelect_clicked();

    void on_doneButton_clicked();

private:
    Ui::lineMarkerControls *ui;
};

#endif // LINEMARKERCONTROLS_H
