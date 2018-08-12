﻿#include "Phonograph.h"
#include <QPainter>


Phonograph::Phonograph(QWidget* parent):QWidget(parent),
    YoffsetOfDisk(76),
    maxAngleOfArm(36),
    currentDiskAngle(0),
    currentArmAngle(0),
    playing(false),
    AlbumCover(":/resource/image/AlbumCover1.jpg"),
    disk(":/resource/image/netease_disk.png"),
    toneArm(":/resource/image/netease_tone_arm.png")
    ,backgroundColor("#00000000")
{
    setMouseTracking(true);
    timerDisk = new QTimer(this);              //唱片转动定时器
    timerArm = new QTimer(this);               //唱臂转动定时器

    timerDisk->setInterval(30);                 //人眼能分辨的每秒帧率一般在24-30帧,这里设置30间隔以上，每秒帧数约等于33帧
    timerArm->setInterval(30);

    connect(timerDisk,SIGNAL(timeout()),this,SLOT(updateAngleOfDisk()));
    connect(timerArm,SIGNAL(timeout()),this,SLOT(updateAngleOfArm()));

}

void Phonograph::setAlbumCover(QPixmap cover)
{
    AlbumCover = cover;
}

void Phonograph::play()
{
    playing = true;

    if(!timerDisk->isActive())    //未被启动时才启动
        timerDisk->start();
    if(!timerArm->isActive())     //未被启动时才启动
        timerArm->start();
}

void Phonograph::stop()
{
    playing = false;

    if(!timerArm->isActive())   //如果唱臂定时器已经关闭，启动定时器
        timerArm->start();
}

//查询是否在播放
bool Phonograph::isPlaying()
{
    return playing;
}

void Phonograph::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);

    QRect outerRect(0,0,this->width()-1,this->height()-1);
    painter.fillRect(outerRect, QBrush(backgroundColor));                   //绘制背景颜色
    QWidget::paintEvent(event);

////////////////////////////////////////////////////////////////////

    //绘制相关参数计算
    int albumWidth = 400;
    int albumHeight = 400;
    QPoint albumBase(this->width()/2-albumWidth/2, YoffsetOfDisk);                      //唱片左上角位置
    QPoint albumCenter(albumBase.x() + albumWidth/2, albumBase.y() + albumHeight/2);    //唱片中心点位置

    int toneArmWidth = 200;
    int toneArmHeight = 100;
    QPoint rotatePointOfArm(20,20);                 //唱臂图片上旋转的点
    QPoint ArmRotatePoint(this->width()/2, 0);      //唱臂在整个控件中旋转的点

//////////////////////////////////////////////////////////////////////

    painter.save();         //状态入栈

    //绘制唱片
    painter.translate(albumCenter);     //设置中心点到唱片要在整个控件上放置的中心点位置
    painter.rotate(currentDiskAngle * 1.0 / 10);

    painter.save();

    painter.scale(0.66,0.66);

    QPixmap pix = AlbumCover.scaled(albumWidth, albumHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(- albumWidth/2, - albumHeight/2,albumWidth, albumHeight,pix);

    painter.restore();

    pix = disk.scaled(albumWidth, albumHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(- albumWidth/2, - albumHeight/2,albumWidth, albumHeight,pix);

    painter.restore();      //恢复之前状态

//////////////////////////////////////////////////////////////

    painter.save();         //状态入栈
    //绘制唱臂
    painter.translate(ArmRotatePoint);     //设置在整个控件上旋转点
    painter.rotate(currentArmAngle);

    pix = toneArm.scaled(toneArmWidth, toneArmHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap( - rotatePointOfArm.x(), - rotatePointOfArm.y(), toneArmWidth, toneArmHeight, pix);

    painter.restore();      //恢复之前状态

}


void Phonograph::updateAngleOfDisk()
{
    if(playing)
    {
        currentDiskAngle += 3; //每帧转动 0.3 度

        currentDiskAngle = currentDiskAngle % 3600;  // 0.1 * 3600 = 360

        update();
    }
    else
        timerDisk->stop();      //已经被要求停止，停止定时器
}

void Phonograph::updateAngleOfArm()
{
    if(playing && currentArmAngle != maxAngleOfArm) //播放中，但是磁头没到位，则转动一下
    {
        currentArmAngle+=6;  // 每帧转动6度

        if(currentArmAngle > maxAngleOfArm)
            currentArmAngle = maxAngleOfArm;

        update();
    }

    if(!playing && currentArmAngle != 0)  //已经没在播放，却没有复位，则转动一下
    {
        currentArmAngle-=6;

        if(currentArmAngle < 0)
            currentArmAngle = 0;
        update();
    }

    if((playing && currentArmAngle == maxAngleOfArm) ||
            (!playing && currentArmAngle == 0))
    {
        timerArm->stop(); //唱臂到位，停止定时器
    }

}
