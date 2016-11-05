#include "Settings.h"
#include <QFile>
#include <QJsonDocument>
#include <QDebug>

const QString Settings::savePath = "./settings.json";

Settings::Settings(QObject *parent) : QObject(parent)
{

}

bool Settings::load()
{
    QFile file(savePath);
    if(!file.open(QIODevice::ReadOnly)) {
        loadDefault();
        return true;
    }
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    this->settings = d.object();
    file.close();
    return true;
}

bool Settings::save()
{
    QFile file(savePath);
    if(!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    QJsonDocument d(this->settings);
    file.write(d.toJson());
    file.close();
    return true;
}

void Settings::loadDefault()
{
    this->settings = QJsonObject();
    QJsonObject sGeneral, sScripts;
    sGeneral["directory"] = "/home/tomoaki-usual/hdd/Downloads";
    sScripts["path"] = "/home/tomoaki-usual/test.sh";
    this->settings["general"] = sGeneral;
    this->settings["scripts"] = sScripts;
}
