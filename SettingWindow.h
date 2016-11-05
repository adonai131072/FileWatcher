#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QJsonObject>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>
#include "Settings.h"


namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

    QWebEngineView *webView;
    QWebChannel *channel;
    Settings *settings;

public:
    explicit SettingWindow(Settings *setting, QWidget *parent = 0);
    ~SettingWindow();

private:
    Ui::SettingWindow *ui;

signals:
    void init(QJsonObject);

public slots:
    Q_INVOKABLE void canceled();
    Q_INVOKABLE void OKed(QString);
    Q_INVOKABLE void htmlInit();

};

#endif // SETTINGS_H
