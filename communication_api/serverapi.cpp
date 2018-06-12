#include "serverapi.h"

ServerApi::ServerApi()
    : hostName{"http://localhost/api/v1/checkTicket"},
      userName{"manager"},
      password{"smb2017"},
      networkManager{new QNetworkAccessManager(this)},
      networkRepliesHashMap{new QHash<QString, QNetworkReply*>()},
      networkRepliesMapper{new QSignalMapper(this)},
      repliesCount{}
{
    QObject::connect(networkRepliesMapper, SIGNAL(mapped(QString)), this, SLOT(handleLogin(QString)));
}

void ServerApi::login()
{
    QNetworkReply* reply{networkManager->get(QNetworkRequest(QUrl(hostName)))};
    QString replyID{QString::number(++repliesCount)};
    networkRepliesHashMap->insert(replyID, reply);
    networkRepliesMapper->setMapping(reply, replyID);
    QObject::connect(reply, SIGNAL(finished()), networkRepliesMapper, SLOT(map()));
    //QObject::connect(reply, SIGNAL(finished()), this, SLOT(donothing()));
}

void ServerApi::handleLogin(QString replyID)
{
    cout << "GERRERRE";
    QNetworkReply* reply{networkRepliesHashMap->value(replyID)};
    if (reply->error())
    {
        cout << "ERROR";
        cout << reply->errorString().toStdString() << endl;
    }
    else
        cout << ":3" << endl;
    reply->deleteLater();
}

void ServerApi::donothing()
{

}
