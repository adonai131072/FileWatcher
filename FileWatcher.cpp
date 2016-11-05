#include "FileWatcher.h"
#include <QDebug>


FileWatcher::FileWatcher()
{
}

FileWatcher::~FileWatcher()
{
    for(Directory *d : this->dlist) {
        delete d;
    }
}

void FileWatcher::addDirectory(QString dir)
{
    QDir newD(dir);
    auto p = std::find_if(this->dlist.cbegin(), this->dlist.cend(), [&](const Directory * const d){
        return newD == d->getPath();
    });
    if(p != this->dlist.cend()) {
        return;
    }

    Directory *d = new Directory(dir);

    this->dlist.append(d);

    connect(d, &Directory::fileAdded, [=](const QFileInfoList &list) {
        emit this->fileAdded(list);
    });
    connect(d, &Directory::fileDeleted, [=](const QFileInfoList &list) {
        emit this->fileDeleted(list);
    });
    connect(d, &Directory::fileChanged, [=](const QFileInfoList &list) {
        emit this->fileChanged(list);
    });

    qDebug() << "listening directory: " << dir;
}

QList<QDir> FileWatcher::getList() const
{
    QList<QDir> ret;
    for(const Directory * const d : this->dlist) {
        ret.append(d->getPath());
    }
    return ret;
}
