#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QJsonObject>

class Settings : public QObject
{
    Q_OBJECT

    static const QString savePath;

public:
    Settings(QObject *parent = 0);

    QJsonObject settings;

    bool save();
    bool load();
    void loadDefault();

};

#endif // SETTINGS_H
