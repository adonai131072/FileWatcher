#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QtWebChannel/QtWebChannel>
#include <QJsonArray>
#include <QFileInfoList>
#include "Settings.h"
#include "SettingWindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QWebEngineView *webView;
    QWebChannel *channel;
    Settings *settings;

public:
    explicit MainWindow(Settings *s, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void test(QJsonArray);
    void dirAdded(QString);

public slots:
    Q_INVOKABLE void htmlInit();
    Q_INVOKABLE void addDirectory(QString);
    void fileAdd(const QFileInfoList &list);
    void onSettings();
    void onExecEnd();

};

#endif // MAINWINDOW_H
