#ifndef __Solicitud__
#define __Solicitud__
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud()
{
    socketlocal = new SocketDatagrama(0);
}

char * Solicitud::doOperation(char *IP, int puerto, int operationId, int requestId, char *arguments)
{
    struct mensaje sol,res;
    
    sol.messageType = 0;
    sol.requestId = requestId;
    strcpy(sol.IP,IP);
    sol.operationId = operationId;
    sol.puerto = puerto;
    strcpy(sol.arguments,arguments);
    strcpy(res.arguments,"El servidor no esta disponible intente mas tarde...");
    int i = 0,regreso = 0;
    PaqueteDatagrama Cliente((char *)&sol,sizeof(sol),IP,puerto);
    PaqueteDatagrama Servidor(sizeof(struct mensaje));

    //operacion 1
    if(operationId == 1){
        while(i<7){          
            socketlocal->envia(Cliente);
            regreso = socketlocal->recibeTimeout(Servidor,2,500000);
            memcpy(&res,Servidor.obtieneDatos(),sizeof(struct mensaje));
            printf("operation 1: %s\n",res.arguments);
            if(regreso < 0){
                i++;
            }else{
                break;
            }
        }            
    }
    //operacion 2
    if(operationId == 2){
        while(i<7){   
            socketlocal->envia(Cliente);
            regreso = socketlocal->recibeTimeout(Servidor,2,500000);
            if(regreso < 0){
                i++;
            }else{
                memcpy(&res,Servidor.obtieneDatos(),sizeof(struct mensaje));
                printf("operation 2: %s\n",res.arguments);
                return (char *)((struct mensaje *)Servidor.obtieneDatos())->arguments;
            }
        }
    }
    //operacion 3
    if(operationId == 3){
        struct timeval tv1,tv2,tv3,tv4,act,dif;
        time_t t1,t2,t3,t4;
        long actual;     
        gettimeofday(&tv1,NULL);
        t1 = (tv1.tv_sec*100) + (tv1.tv_usec)/1000;
        printf("\ntiempo 1: %ld\n",t1);           
        while(i<7){   
            socketlocal->envia(Cliente);
            regreso = socketlocal->recibeTimeout(Servidor,2,500000);
            if(regreso < 0){
                i++;
            }else{
                gettimeofday(&tv4,NULL);
                //t4 = (tv.tv_sec*100) + (tv.tv_usec)/1000;  
                //printf("\ntiempo 4: %ld\n",t4);
                memcpy(&res,Servidor.obtieneDatos(),sizeof(struct mensaje));
                memcpy(&tv3,res.arguments,sizeof(struct timeval));
                //t3 = atol(res.arguments);
                //printf("\ntiempo 3: %ld\n",t3);
                timersub(&tv4,&tv1,&act);
                act.tv_sec=act.tv_sec/2;
                act.tv_usec=act.tv_usec/2;
                timeradd(&tv3,&act,&dif);
		settimeofday(&dif,NULL);
                struct tm * timeinfo;
                t1 = dif.tv_sec;
                timeinfo = localtime (&t1);                   
                //actual = t3 + (t4-t1)/2;
                sprintf(res.arguments, "%s", asctime(timeinfo));
                printf("operation 3: %s\n",res.arguments);
                return (char *)((struct mensaje *)Servidor.obtieneDatos())->arguments;
            }
        }
    } 
    memcpy(&res,Servidor.obtieneDatos(),sizeof(struct mensaje));

    return (char *)((struct mensaje *)Servidor.obtieneDatos())->arguments;    
}
#endif
