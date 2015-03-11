#-------------------------------------------------
#
# Project created by QtCreator 2013-11-20T18:49:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brontossauro
TEMPLATE = app


SOURCES += brontossaurus/sources/mainwindow.cpp \
    brontossaurus/sources/main.cpp \
    brontossaurus/sources/janeladecalibragem.cpp \
    brontossaurus/sources/camera.cpp

HEADERS  += brontossaurus/sources/mainwindow.h \
    brontossaurus/sources/janeladecalibragem.h \
    brontossaurus/sources/camera.h

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree

FORMS    += brontossaurus/sources/mainwindow.ui \
    brontossaurus/sources/janeladecalibragem.ui

OTHER_FILES += \
    ../findheight/brontossauro.png

RESOURCES += \
    resource.qrc
