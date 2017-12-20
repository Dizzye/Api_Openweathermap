#include "weather.h"


Weather::Weather()
{

}

QUrl Weather::getUrl()
{
    QUrl url("https://api.openweathermap.org/data/2.5/weather");
    query.addQueryItem("appid", API_KEY);
    url.setQuery(query);
    return url;



}

 void Weather::addQuery(QString key, QString value)
{
    this->query.addQueryItem(key,value);
}

void Weather::clear()
{
    query.clear();
}

