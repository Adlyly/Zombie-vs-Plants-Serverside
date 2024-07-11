#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    void initializeRoles();
    ~Server();
private :
    QTcpServer* MyServer;
    QList<QTcpSocket*> MySockets;
    QList<bool> PlantOrZombie; //0 means zombie and 1 means plant,
    // each socket has it boolian in the same place ( i mean first socket refers to first boolian and second to second
    int flag=0;
    // int round;
public slots:
    void NewConnection();
    void ReadingData();
    void WritingData();
    //void ConnectedToServer();
    void DisconnectedFromServer(QTcpSocket *_socket);
};

#endif // SERVER_H
