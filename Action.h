#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QProcess>
#include <QFileInfo>

class Action : public QObject
{
    Q_OBJECT

public:
    Action(QObject *parent = 0) : QObject(parent) {}
    virtual void Do(const QFileInfo &fi) {}

signals:
    void done();
    void error(int code);

};

#endif // ACTION_H
