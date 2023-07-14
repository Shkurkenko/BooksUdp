#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QObject>
#include <QUdpSocket>

class UDPClient : public QObject
{
    Q_OBJECT
public:
    explicit UDPClient(QObject *parent = nullptr);
    void SendBookName(const QByteArray name);
signals:
    void DataRecieved(QJsonObject &data);
public slots:
    void ReadDatagram();
private:
    QUdpSocket *socket;
private:
    QJsonObject ObjectFromString(const QString& in)
    {
        QJsonObject obj;

        QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

        // check validity of the document
        if(!doc.isNull())
        {
            if(doc.isObject())
            {
                obj = doc.object();
            }
            else
            {
                qDebug() << "Document is not an object" << '\n';
            }
        }
        else
        {
            qDebug() << "Invalid JSON...\n" << in << '\n';
        }

        return obj;
    }

};

#endif // UDPCLIENT_H
