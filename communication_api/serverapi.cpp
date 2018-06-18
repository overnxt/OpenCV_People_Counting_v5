#include "serverapi.h"

ServerApi::ServerApi()
    : hostName{"http://localhost"},
      userName{"manager"},
      password{"smb2017"},
      networkManager{new QNetworkAccessManager(this)},
      networkRepliesHashMap{new QHash<QString, QNetworkReply*>()},
      networkRepliesMapper{new QSignalMapper(this)},
      repliesCount{},
      apiUpdateBusLatLong{"/api/v1/updateBusPosition"}
{
    QObject::connect(networkRepliesMapper, SIGNAL(mapped(QString)), this, SLOT(handleLogin(QString)));
}

void ServerApi::updateLatLongBus(int busID, int peopleIn1, int peopleIn2, int peopleOu1, int peopleOu2)
{
    QByteArray postData;
    postData.append(QString("busId=%1&").arg(busID));
    postData.append(QString("peopleOut1=%1&").arg(peopleOu1));
    postData.append(QString("peopleOut2=%1&").arg(peopleOu2));
    postData.append(QString("peopleIn1=%1&").arg(peopleIn1));
    postData.append(QString("peopleIn2=%1").arg(peopleIn2));
    QNetworkRequest requset(QUrl(hostName + apiUpdateBusLatLong));
    requset.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    QNetworkReply* reply{networkManager->post(requset, postData)};
    QString replyID{QString::number(++repliesCount)};
    networkRepliesHashMap->insert(replyID, reply);
    networkRepliesMapper->setMapping(reply, replyID);
    QObject::connect(reply, SIGNAL(finished()), networkRepliesMapper, SLOT(map()));
    //QObject::connect(reply, SIGNAL(finished()), this, SLOT(donothing()));
}

void ServerApi::handleLogin(QString replyID)
{
    QNetworkReply* reply{networkRepliesHashMap->value(replyID)};
    if (reply->error())
    {
        cout << "ERROR";
        cout << reply->errorString().toStdString() << endl;
    }
    else
        cout << reply->readAll().toStdString() << endl;
    reply->deleteLater();
}
