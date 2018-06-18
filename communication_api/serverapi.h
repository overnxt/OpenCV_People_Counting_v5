#ifndef SERVERAPI_H
#define SERVERAPI_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QHash>
#include <QSignalMapper>
#include <QUrl>
#include <QByteArray>
#include <QUrlQuery>
#include <iostream>
using std::cout;
using std::endl;
class ServerApi : public QObject
{
    Q_OBJECT
private:
    QString hostName;
    QString userName;
    QString password;
    QNetworkAccessManager* networkManager;
    QHash<QString, QNetworkReply*>* networkRepliesHashMap;
    QSignalMapper* networkRepliesMapper;
    int repliesCount;
    QString apiUpdateBusLatLong;
public:
    ServerApi();
    void updateLatLongBus(int busID, int peopleIn1, int peopleIn2, int peopleOu1, int peopleOu2);

public slots:
    void handleLogin(QString replyID);
};

#endif // SERVERAPI_H
