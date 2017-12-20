#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "weather.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    connect(&manager, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinish(QNetworkReply*)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Weather pocasi;
    pocasi.addQuery("q",ui->lineEdit->text());
    QNetworkRequest request;
    qDebug()<< pocasi.getUrl();
    request.setUrl(pocasi.getUrl());
    manager.get(request);

}


void MainWindow::downloadFinish(QNetworkReply *reply)
{


    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject doc_obj = doc.object();
    QJsonArray weather = doc_obj["weather"].toArray();
    QJsonObject majn = doc_obj["main"].toObject();

    if (!ui->lineEdit->text().isEmpty()) {
        QJsonObject sys = doc_obj["sys"].toObject();
        QNetworkRequest request;
        ui->textBrowser->setText("<p style='font-size:15px'><a style='color:red'>" + ui->lineEdit->text() + ", " + sys["country"].toString() + "</a>"
                                 + " " + weather.at(0).toObject()["description"].toString() + "<br>" + "Teplota v tomto místě je : " +
                                QString::number(majn["temp"].toDouble()-272.15)+ "°С" + "</p>"

                );

    }else{
       QMessageBox::warning(this,"Chyba!","Zadejte město ve kterém chcete zjistit počasí !");
    }

   }



