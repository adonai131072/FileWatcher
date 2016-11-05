#include "MainWindow.h"
#include <QApplication>
#include "FileWatcher.h"
#include "Settings.h"
#include <QFileInfoList>


void link(FileWatcher *fw, MainWindow *w)
{
    QObject::connect(fw, &FileWatcher::fileAdded, w, &MainWindow::fileAdd);
    QObject::connect(w, &MainWindow::dirAdded, fw, &FileWatcher::addDirectory);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings s;

    s.load();

    FileWatcher fw;
    MainWindow w(&s);

    link(&fw, &w);

    w.show();

    int ret = a.exec();

    s.save();
    return ret;
}
