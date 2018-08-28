#include "gpstools.h"

#include <QTcpServer>
#include <QTcpSocket>

GpsTools::GpsTools(QObject *parent) : QObject(parent)
{
    tcp = new QTcpServer();
    tcp->listen(QHostAddress::Any, 9070);
    connect(tcp, SIGNAL(newConnection()),this, SLOT(newConnection()));
    gps.lat = 39;
    gps.lng = 38;
}

GPS GpsTools::getGpsData()
{
    return gps;
}

void GpsTools::newConnection()
{
    sock = tcp->nextPendingConnection();
    qDebug() << "new connection" << sock->peerAddress().toString() << sock->peerPort();
    connect(sock, SIGNAL(readyRead()), this, SLOT(newData()));
}

void GpsTools::newData()
{
    QString data = QString::fromLatin1(sock->readAll()).split("\n").first();
    qDebug() << "incoming data " << data;
    QStringList flds = data.split(";");
    gps.lat = flds.first().toFloat();
    gps.lng = flds.last().toFloat();
}
