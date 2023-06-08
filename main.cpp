
#include "mdi_test.h"
#include "tableMdi.h"
#include "curveMdi.h"

#include <QApplication>
#include <QMdiArea>
#include <QMdiSubWindow>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mdi_test w;
    w.show();
    return a.exec();
}

//// 在使用中的示例
//int main(int argc, char *argv[])
//{
//    QApplication app(argc, argv);

//    QMdiArea mdiArea;
//    QMainWindow mainWindow;
//    mainWindow.setCentralWidget(&mdiArea);

//    QMdiSubWindow *subWindow = new QMdiSubWindow(&mdiArea);
//    TableMdiChild *tableMdiChild = new TableMdiChild(subWindow);
//    subWindow->setWidget(tableMdiChild);
//    mdiArea.addSubWindow(subWindow);

//    mainWindow.show();

//    return app.exec();
//}
