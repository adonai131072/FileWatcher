#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <QObject>
#include "Directory.h"
#include <QList>
#include <QFileInfoList>


class FileWatcher : public QObject
{
    Q_OBJECT

    QList<Directory *> dlist;

public:
    FileWatcher();
    ~FileWatcher();

    QList<QDir> getList() const;

signals:
    void fileChanged(const QFileInfoList &files);
    void fileAdded(const QFileInfoList &files);
    void fileDeleted(const QFileInfoList &files);

public slots:
    void addDirectory(QString dir);

};

#endif // FILEWATCHER_H
