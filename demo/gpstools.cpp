#include "gpstools.h"

#include <QTcpSocket>

GpsTools::GpsTools(QObject *parent) : QObject(parent)
{
	sock = new QTcpSocket();
	sock->connectToHost("172.1.1.1", 9070);
	connect(sock, SIGNAL(connected()), SLOT(newConnection()));
	connect(sock, SIGNAL(readyRead()), SLOT(newData()));
	gps.lat = 39;
    gps.lng = 38;
}

GPS GpsTools::getGpsData()
{
    return gps;
}

void GpsTools::newConnection()
{
	qDebug() << "connected";
}

void GpsTools::newData()
{
    QString data = QString::fromLatin1(sock->readAll()).split("\n").first();
    qDebug() << "incoming data " << data;
    QStringList flds = data.split(";");
    gps.lat = flds.first().toFloat();
	gps.lng = flds.at(1).toFloat();
}
