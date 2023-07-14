#include "udpclient.h"

UDPClient::UDPClient(QObject *parent)
    : QObject{parent}
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 9999);
    connect(socket, SIGNAL(readyRead()), this, SLOT(ReadDatagram()));
}

void UDPClient::SendBookName(const QByteArray name)
{
    socket->writeDatagram(name, QHostAddress::LocalHost, 8888);
}

void UDPClient::ReadDatagram()
{
    QByteArray Data;
    Data.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Data.data(), Data.size(), &sender, &senderPort);

    QString DataAsString = QString(Data);
    qDebug() << DataAsString;
    QJsonObject DataObj = ObjectFromString(DataAsString);

    emit(DataRecieved(DataObj));
}
