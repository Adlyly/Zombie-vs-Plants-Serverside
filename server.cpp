#include "server.h"

Server::Server() {
    MyServer = new QTcpServer();
    MyServer->listen(QHostAddress::Any , 1025);
    // This use to see if our server is listening or not
    if(!MyServer->isListening()){
        qDebug() << "ERROR\n";
    }
    else{
        qDebug() << "Listening...\n";
        while(true){
            connect(MyServer , SIGNAL(newConnection()) , this , SLOT(NewConnection)); // This slot wait for new connection
        }
    }
}

void Server::initializeRules()
{

}

void Server::NewConnection()
{
    QTcpSocket * new_client = MyServer->nextPendingConnection();
    new_client->setObjectName("Client " + QString::number(MySockets.size() + 1));
    MySockets.append(new_client);
    connect(new_client, &QTcpSocket::connected, this, &Server::ConnectedToServer);
    connect(new_client, &QIODevice::readyRead, this, [this, new_client](){ ReadingData(new_client); });
    connect(new_client, &QIODevice::bytesWritten, this, [this, new_client](){ WritingData(new_client); });
    connect(new_client, &QAbstractSocket::disconnected, this, [this, new_client](){ DisconnectedFromServer(new_client); });
}

void Server::ReadingData(QTcpSocket *_socket)
{
    //it should give a json file and send it to another client
    // if the clients send a boolian to server it means that the game has finished
    // if the boolian was 0 it means that was first rand and they should play again
    // if the boolian was 1 it means that they play for two rond and the game is finished
}

void Server::WritingData(QTcpSocket *_socket)
{
    qDebug() << "written Successfully\n";
    //used to say that writing is finished
}

void Server::ConnectedToServer()
{
    qDebug() << "Connected Successfully\n";
    if(MySockets.size()==2)
        //call a function to send data
    //we should give the clients a boolian to see one of them as a plant and other as a zombie
}

void Server::DisconnectedFromServer(QTcpSocket *_socket)
{
    MySockets.removeOne(_socket);

    for (int var = 0; var < MySockets.size(); ++var)
    {
        MySockets[var]->setObjectName("Client " + QString::number(var + 1));
    }

    _socket->deleteLater();
}

Server::~Server()
{
    delete MyServer;
    //delete []MySockets;
}


