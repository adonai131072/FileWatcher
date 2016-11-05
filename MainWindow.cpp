#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "ActionLinux.h"

#include <QStackedLayout>
#include <QJsonObject>
#include <QDebug>


QString fileTypeToStr(const QFileInfo &fi)
{
    if(fi.isDir()) {
        return "directory";
    }
    else if(fi.isFile()) {
        return "file";
    }
}

MainWindow::MainWindow(Settings *s, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(s)
{
    ui->setupUi(this);

    this->webView = new QWebEngineView(this);
    this->channel = new QWebChannel(this);
    this->channel->registerObject(QString("mainWindow"), this);

    QStackedLayout *layout = new QStackedLayout;
    ui->centralWidget->setLayout(layout);

    layout->addWidget(this->webView);

    this->webView->load(QUrl("qrc:///index.html"));
    this->webView->page()->setWebChannel(this->channel);

    connect(ui->menuFairu, SIGNAL(triggered(QAction*)), this, SLOT(onSettings()));
}

MainWindow::~MainWindow()
{
    settings->save();
    delete ui;
}

void MainWindow::htmlInit()
{
    addDirectory(settings->settings["general"].toObject()["directory"].toString());
}

void MainWindow::addDirectory(QString dir)
{
    emit this->dirAdded(dir);
}

void MainWindow::fileAdd(const QFileInfoList &list)
{
    QJsonArray arr;
    for(const QFileInfo &fi : list) {
        qDebug() << "file added: " << fi.absoluteFilePath();

        arr.append(QJsonObject({
                                   QPair<QString, QJsonValue>("name", fi.fileName()),
                                   QPair<QString, QJsonValue>("path", fi.absolutePath()),
                                   QPair<QString, QJsonValue>("type", fileTypeToStr(fi)),
                               }));

        Action *a = new ActionLinux(this, settings->settings["scripts"].toObject()["path"].toString());
        connect(a, SIGNAL(done()), this, SLOT(onExecEnd()));
        a->Do(fi);
    }
    emit this->test(arr);
}

void MainWindow::onSettings()
{
    SettingWindow *settingWindow = new SettingWindow(settings);
    qDebug() << settingWindow->exec();
}

void MainWindow::onExecEnd()
{
    qDebug() << "EXEC END.";
}
