#-------------------------------------------------
#
# Project created by QtCreator 2018-07-05T22:26:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Beslyric-for-X
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


INCLUDEPATH +=$$PWD BesWidgets
include(BesWidgets/BesWidgets.pri)

INCLUDEPATH +=$$PWD StackFrame
include(StackFrame/StackFrame.pri)

INCLUDEPATH +=$$PWD TopWidgets
include(TopWidgets/TopWidgets.pri)

INCLUDEPATH +=$$PWD MiddleWidgets
include(MiddleWidgets/MiddleWidgets.pri)

INCLUDEPATH +=$$PWD BottomWidgets
include(BottomWidgets/BottomWidgets.pri)

INCLUDEPATH +=$$PWD Entities
include(Entities/Entities.pri)

INCLUDEPATH +=$$PWD Utility
include(Utility/Utility.pri)


SOURCES += main.cpp \
    StackFrame.cpp

HEADERS  += \
    Define/Define.h\
    Define/Enum.h\
    Define/Struct.h\
    Define/Static.h\
    global.h \
    StackFrame.h \
    MyApplication.h

DISTFILES +=

RESOURCES += \
    resource.qrc

win32 {
    ffmpeg_bin_dir = $$PWD\beslyric-lib\win32\ffmpeg_4_0_1\bin\*.*
    sdl_bin_dir = $$PWD\beslyric-lib\SDL_2_0_3\bin\*.*
    CONFIG(debug, debug|release) {
        dst_dir = $$OUT_PWD\\debug\\
    } else {
        dst_dir = $$OUT_PWD\\release\\
    }

    # dst_dir 最后的 \\ 是必须的，用来标示 xcopy 到一个文件夹，若不存在，创建之

    # Replace slashes in paths with backslashes for Windows
    ffmpeg_bin_dir ~= s,/,\\,g
    sdl_bin_dir ~= s,/,\\,g
    dst_dir ~= s,/,\\,g

    system(xcopy $$ffmpeg_bin_dir $$dst_dir /y /e)
    system(xcopy $$sdl_bin_dir $$dst_dir /y /e)
}
