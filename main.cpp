#include "StackFrame.h"
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

    StackFrame MainFrameWidget(&app);
    app.SetMakingLyricNotifyWidget(MainFrameWidget.mainWidget);
    app.SetStackFrame(&MainFrameWidget);
    MainFrameWidget.show();

    return app.exec();
}
