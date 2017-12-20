#ifndef WEATHER_H
#define WEATHER_H
#define API_KEY "f7c547a2be514d5ac67554faa9bba985"
#include <QString>
#include <QUrlQuery>
#include "mainwindow.h"


class Weather
{
public:
    Weather();


  QUrl getUrl();
   void addQuery(QString key, QString value);
    void clear();

private:
    QUrlQuery query;


};

#endif // WEATHER_H
