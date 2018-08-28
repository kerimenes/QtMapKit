#ifndef GPSTOOLS_H
#define GPSTOOLS_H

#include <QObject>

struct GPS{
    float lat;
    float lng;
};

class QTcpServer;
class QTcpSocket;
class GpsTools : public QObject
{
    Q_OBJECT
public:
    explicit GpsTools(QObject *parent = 0);

    GPS getGpsData();
signals:

public slots:
protected slots:
    void newConnection();
    void newData();
private:
    QTcpServer *tcp;
    QTcpSocket *sock;
    GPS gps;
};

#endif // GPSTOOLS_H
