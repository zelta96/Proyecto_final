#include "SocketDatagrama.h"
#include <errno.h>
#include <iostream>
#include <unistd.h>
#include <sys/time.h>


using namespace std;


SocketDatagrama::SocketDatagrama(int puerto)
{
    s = socket(AF_INET, SOCK_DGRAM, 0);
    bzero((char *)&direccionLocal, sizeof(direccionLocal));
    direccionLocal.sin_family = AF_INET;
    direccionLocal.sin_addr.s_addr = INADDR_ANY;
    direccionLocal.sin_port = htons(puerto);
    bind(s, (struct sockaddr *)&direccionLocal,sizeof(direccionLocal));
}

SocketDatagrama::~SocketDatagrama()
{
    close(s);
}


int SocketDatagrama::recibe(PaqueteDatagrama & p)
{
    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    int regreso = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);

    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    //cout << "Mensaje recibido de: " << inet_ntoa(direccionForanea.sin_addr) << ":" << ntohs(direccionForanea.sin_port) << endl;
    return regreso;
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos)
{
    //set timeout...
    timeout.tv_sec = segundos;
    timeout.tv_usec = microsegundos;
    setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));   
     
    unsigned int addr_len = sizeof(direccionForanea);
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    int regreso = recvfrom(s,p.obtieneDatos(),p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &addr_len);
    if(regreso<0){
        if(errno==EWOULDBLOCK){
              fprintf(stderr, "Tiempo de recepción transcurrido\n");
        }
        else{
              fprintf(stderr, "Error en recvfrom\n");
        }

    }
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp(inet_ntoa(direccionForanea.sin_addr));
    //cout << "Mensaje recibido de: " << inet_ntoa(direccionForanea.sin_addr) << ":" << ntohs(direccionForanea.sin_port) << endl;
    return regreso;
}


int SocketDatagrama::envia(PaqueteDatagrama & p)
{
    bzero((char *)&direccionForanea, sizeof(direccionForanea));
    direccionForanea.sin_family = AF_INET;
    direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
    direccionForanea.sin_port = htons(p.obtienePuerto());

    return sendto(s,p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, sizeof(direccionForanea));
}

