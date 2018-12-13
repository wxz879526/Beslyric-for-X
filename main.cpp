#include "MainWindow.h"
#include "AppHelper.h"
#include "MyApplication.h"

//------------------- test ----------------------
#include "BesMessageBox.h"
#include "Define/Define.h"
#include "LyricSearcherFactory/LyricSearcherFactory.h"
#include <QDebug>

#include <LyricListManager.h>

int main(int argc, char *argv[])
{
    MyApplication app(argc, argv);

    MainWindow mainFrameWidget(&app);
    app.SetMakingLyricNotifyWidget(mainFrameWidget.mainWidget);
    app.SetStackFrame(&mainFrameWidget);
    mainFrameWidget.show();

    return app.exec();
}
