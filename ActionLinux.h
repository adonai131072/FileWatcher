#ifndef ACTIONLINUX_H
#define ACTIONLINUX_H

#include "Action.h"

class ActionLinux : public Action
{
    Q_OBJECT

    QString ppath_;

public:
    ActionLinux(QObject *parent = 0) : Action(parent), ppath_("") {}
    ActionLinux(QObject *parent, const QString &ppath) : Action(parent), ppath_(ppath) {}
    virtual void Do(const QFileInfo &fi);

public slots:
    void linuxDone(int code);

};

#endif // ACTIONLINUX_H
