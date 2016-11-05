#include "ActionLinux.h"

void ActionLinux::Do(const QFileInfo &fi)
{
    QProcess *p = new QProcess(this);
    connect(p, SIGNAL(finished(int)), this, SLOT(linuxDone(int)));
    QStringList arg;
    arg << fi.absoluteFilePath();
    p->start(this->ppath_, arg);
}

void ActionLinux::linuxDone(int code)
{
    if(code == 0) {
        emit this->done();
    }
    else {
        emit this->error(code);
    }
}
