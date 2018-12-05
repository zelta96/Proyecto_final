#ifndef __SocketDatagrama__
#define __SocketDatagrama__

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "PaqueteDatagrama.h"
#include <arpa/inet.h>
#include <sys/time.h>

class SocketDatagrama{

public:
    SocketDatagrama(int = 0);
    ~SocketDatagrama();
    //Recibe un paquete tipo datagrama proveniente de este socket
    int recibe(PaqueteDatagrama & p);
    //Envía un paquete tipo datagrama desde este socket
    int envia(PaqueteDatagrama & p);
    //Recibe un paquete tipo datagrama proveniente de este socket en un tiempo determinado
    int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);
private:
    struct sockaddr_in direccionLocal;
    struct sockaddr_in direccionForanea;
    int s; //ID socket
	struct timeval timeout; //struct timeval
};

#endif /* defined(____SocketDatagrama__) */
