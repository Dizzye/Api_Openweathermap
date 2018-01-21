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
    connect(&manager_predpoved, SIGNAL(finished(QNetworkReply*)), SLOT(downloadFinish_predpoved(QNetworkReply*)));


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


    // dalsi querryna pro předpověď
    pocasi.addQuery("q", ui->lineEdit->text());
    QNetworkRequest request_forecast;
    qDebug()<< pocasi.getUrl_Predpoved();
    request_forecast.setUrl(pocasi.getUrl_Predpoved());
    manager_predpoved.get(request_forecast);

}


void MainWindow::downloadFinish(QNetworkReply *reply)
{


    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject document_object = doc.object();
    QJsonArray pocasi = document_object["weather"].toArray();
    QJsonObject main = document_object["main"].toObject();
    QJsonObject wind = document_object["wind"].toObject();

    if (!ui->lineEdit->text().isEmpty()) {
        QJsonObject sys = document_object["sys"].toObject();
        QNetworkRequest request;
        ui->textBrowser->setText("<p style='font-size:15px'><a style='color:blue'>" + ui->lineEdit->text() + ", " + sys["country"].toString() + "</a>"
                                 + " " + pocasi.at(0).toObject()["description"].toString() + "<br>" + "Current temperature in this City is : " +
                                QString::number(main["temp"].toDouble()-272.15)+ " °С" + "<br>" +"Current wind speed in this City is : "
                                + QString::number(wind["speed"].toDouble()) + " Meters/second" "</p>"



                );

    }else{
       QMessageBox::warning(this,"Chyba!","Zadejte město ve kterém chcete zjistit počasí !");
    }

}

void MainWindow::downloadFinish_predpoved(QNetworkReply *reply)
{
    QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject document_object = doc.object();
    QJsonArray list = document_object["list"].toArray();
    QJsonArray weather = document_object["weather"].toArray();


         // nasazeni casu do lablu
      ui->cas->setText(list.at(3).toObject()["dt_txt"].toString());
       ui->cas2->setText(list.at(6).toObject()["dt_txt"].toString());
        ui->cas3->setText(list.at(9).toObject()["dt_txt"].toString());
         ui->cas4->setText(list.at(12).toObject()["dt_txt"].toString());
        //nasazeni teploty do lablu
       ui->teplota->setText(QString::number(list.at(3).toObject()["main"].toObject()["temp"].toDouble() - 272.15) + "°С");
        ui->teplota2->setText(QString::number(list.at(6).toObject()["main"].toObject()["temp"].toDouble() - 272.15) + "°С");
         ui->teplota3->setText(QString::number(list.at(9).toObject()["main"].toObject()["temp"].toDouble() - 272.15) + "°С");
            ui->teplota4->setText(QString::number(list.at(12).toObject()["main"].toObject()["temp"].toDouble() - 272.15) + "°С");




}



