﻿#ifndef STACKFRAME_H
#define STACKFRAME_H

#include <QApplication>
#include "BesFramelessWidget.h"
#include "MainWidget.h"
#include "SkinBoxWidget.h"
#include "AddLyricItemWidget.h"
#include "BesTransparentLayer.h"

#include "ThreadLogin.h"
#include "ThreadCheckUpdate.h"

/*
 *   StackFrame 程序的主控件类，使用 QStacklayout 布局
 *   包含程序的主体功能控件 和 最外层的“悬浮控件”（如皮肤盒等）
 */
class MainWindow : public BesFramelessWidget
{
    Q_OBJECT

public:
    MainWindow(QApplication* pApplication, QWidget *parent = 0);
    ~MainWindow();

    void initSetting();
    void initLayout();
    void initConnection();
    void initEntity();

    void setBorderMain(int border);

signals:
    void onFinalSkinNameChanged(QString);

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    virtual void resizeEvent(QResizeEvent *event);

public slots:

    void SetSkin(QString skinName, bool bFirstInit = false);
    void SetSpecialSkin(QString skinName, bool bFirstInit = false);  //有一些样式无法实现的效果，放在这里应用

    void toggleMaxRestoreStatus();          //切换最大化和恢复2个状态
    void toggleSkinBox();                   //显示或隐藏皮肤盒
    void toggleAddItemWidget();             //显示或隐藏添加列表项控件

    bool mousePressFilter(QMouseEvent *event);
    bool bringMainToTop();                  //将主程序控件提到最前(生效则返回true)

    void onUpdateResultFound(CheckUpgradeResult);

public:
    bool                    isMainOnTop;            //标记当期主体控件是否在最顶层
    MainWidget*             mainWidget;             //程序的主体功能控件
    BesTransparentLayer*    transparentLayer;       //透明层

    SkinBoxWidget*          skinBoxWidget;          //皮肤盒
    AddLyricItemWidget*     addItemWidget;          //添加列表项的控件
    int                     borderMain;             //边框厚度

    int addItemWidgetLeft;
    int addItemWidgetTop;

    QApplication*           pApp;


private:
    //登录记录
    ThreadLogin login;
    ThreadCheckUpdate checkUpdate;
};

#endif // STACKFRAME_H
