﻿#ifndef TOPWIDGET_H
#define TOPWIDGET_H

#include "global.h"
#include <QWidget>
#include "BesButton.h"
#include <QIcon>
#include <QLabel>

class TopWidget : public QWidget
{
    Q_OBJECT

public:
    TopWidget(QWidget *parent = 0);
    ~TopWidget();

    void initLayout();
    void initConnection();

    virtual void mouseDoubleClickEvent(QMouseEvent* event){Q_UNUSED(event);emit(OnDoubleClick());}

signals:
    void OnDoubleClick();

public:
    QIcon*              icon;
    BesButton*          btnIcon;
    QLabel*             labelTitle;

    BesButton*        btnSkinBox;
    BesButton*        btnSetting;
    BesButton*        btnMini;
    BesButton*        btnMax;
    BesButton*        btnRestore;
    BesButton*        btnClose;
};

#endif // TOPWIDGET_H
