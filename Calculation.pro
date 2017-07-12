#-------------------------------------------------
#
# Project created by QtCreator 2017-07-07T09:25:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Calculation
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    View/View.cpp \
    iqwidget.cpp \
    View/subview.cpp \
    View/qcustomplot/qcustomplot.cpp \
    Model/Function/Cond.cpp \
    Model/Function/Integral.cpp \
    Model/Function/ODE.cpp \
    Model/Function/Root_of_Polynomial.cpp \
    Model/Model.cpp \
    ViewModel/Command/ButtonRunClickCommand.cpp \
    ViewModel/Command/ShowGraphCommand.cpp \
    ViewModel/ViewModel.cpp

HEADERS  += \
    View/View.h \
    iqwidget.h \
    View/subview.h \
    View/qcustomplot/qcustomplot.h \
    Model/Function/Cond.h \
    Model/Function/curve_fitting.h \
    Model/Function/Integral.h \
    Model/Function/ODE.h \
    Model/Function/Root_of_Polynomial.h \
    Model/Model.h \
    Model/Function/matrix.h \
    Common/Notification.h \
    ViewModel/ViewModel.h \
    Common/iCommand.h \
    Common/Params.h \
    Model/Function/eigenvalue.h \
    Model/Function/root_of_matrix.h \
    ViewModel/Command/ShowGraphCommand.h \
    ViewModel/Command/ButtonRunClickCommand.h

FORMS    += \
    View.ui
