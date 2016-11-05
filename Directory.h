#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QObject>
#include <QSharedPointer>
#include <QFileSystemWatcher>
#include <QDir>


class Directory : public QObject
{
    Q_OBJECT

    QFileSystemWatcher *watcher;
    QFileInfoList oldList;
    QDir path;

public:
    Directory();
    Directory(const QString &dir);
    Directory(Directory &&other);
    ~Directory();

    QDir getPath() const { return path; }

public slots:
    void impFileChanged(const QString &path);
    void impDirectoryChanged(const QString &path);

signals:
    void fileChanged(const QFileInfoList &files);
    void fileAdded(const QFileInfoList &files);
    void fileDeleted(const QFileInfoList &files);

};

#endif // DIRECTORY_H
