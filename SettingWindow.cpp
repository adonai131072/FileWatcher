#include "SettingWindow.h"
#include "ui_SettingWindow.h"

SettingWindow::SettingWindow(Settings *setting, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow),
    settings(setting)
{
    ui->setupUi(this);

    this->webView = new QWebEngineView(this);
    this->channel = new QWebChannel(this);
    this->channel->registerObject(QString("settings"), this);

    QStackedLayout *layout = new QStackedLayout;
    ui->widget->setLayout(layout);

    layout->addWidget(this->webView);

    this->webView->load(QUrl("qrc:///settings.html"));
    this->webView->page()->setWebChannel(this->channel);

}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::canceled()
{
    this->reject();
}

void SettingWindow::OKed(QString setting)
{
    QJsonDocument d = QJsonDocument::fromJson(setting.toUtf8());
    settings->settings = d.object();
    this->accept();
}

void SettingWindow::htmlInit()
{
    emit this->init(settings->settings);
}
