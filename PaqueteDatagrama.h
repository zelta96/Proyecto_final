#ifndef __PAQUETEDATAGRAMA__
#define __PAQUETEDATAGRAMA__

#include <iostream>
#include <cstring>

class PaqueteDatagrama {
    public:
        PaqueteDatagrama(char *, unsigned int, const char *, int );
        PaqueteDatagrama(unsigned int );
        ~PaqueteDatagrama(); // Destructor
        char *obtieneDireccion();
        unsigned int obtieneLongitud();
        int obtienePuerto();
        char *obtieneDatos();
        void inicializaPuerto(int);
        void inicializaIp(char *);
        void inicializaDatos(char *);
    private:
        char *datos; //Almacena los datos
        char ip[16]; //Almacena la IP
        unsigned int longitud; //Almacena la longitude de la cadena de datos
        int puerto; //Almacena el puerto
}; 

#endif 