#include "Directory.h"

#include <algorithm>
#include <QFileInfo>
#include <QDateTime>
#include <QDebug>

#include "Algorithm.h"

Directory::Directory()
{
}

Directory::Directory(Directory &&other)
{
    this->path = std::move(other.path);
    this->watcher = other.watcher;
    other.watcher = nullptr;
    this->oldList = std::move(other.oldList);
}

Directory::~Directory()
{
    if(this->watcher) {
        this->watcher->deleteLater();
    }
}

Directory::Directory(const QString &dir) : path(dir)
{
    this->oldList = path.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);

    this->watcher = new QFileSystemWatcher(this);
    this->watcher->addPath(dir);
    connect(this->watcher, SIGNAL(fileChanged(QString)), this, SLOT(impFileChanged(QString)));
    connect(this->watcher, SIGNAL(directoryChanged(QString)), this, SLOT(impDirectoryChanged(QString)));
}

void Directory::impDirectoryChanged(const QString &)
{
    QFileInfoList newList = path.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::Name);
    QFileInfoList delList, addList, updateList;
    QList<std::tuple<QFileInfo, QFileInfo>> sameList;

    Fuhihi::set_change(this->oldList.begin(), this->oldList.end(), newList.begin(), newList.end(),
                       std::inserter(delList, delList.begin()),
                       std::inserter(addList, addList.begin()),
                       std::inserter(sameList, sameList.begin()),
                       [](const QFileInfo &f1, const QFileInfo &f2) {
                           return f1.fileName() < f2.fileName();
                       });

    for(const std::tuple<QFileInfo, QFileInfo> &files : sameList) {
        if(std::get<0>(files).lastModified() < std::get<1>(files).lastModified()) {
            updateList << std::get<1>(files);
        }
    }

    if(delList.count() > 0) {
        emit this->fileDeleted(delList);
    }
    if(addList.count() > 0) {
        emit this->fileAdded(addList);
    }
    if(updateList.count() > 0) {
        emit this->fileChanged(updateList);
    }

    this->oldList = newList;
}

void Directory::impFileChanged(const QString &path)
{
}
