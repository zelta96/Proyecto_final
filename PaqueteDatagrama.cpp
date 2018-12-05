# include "PaqueteDatagrama.h"
# include <string.h>
using namespace std;
 PaqueteDatagrama::PaqueteDatagrama(char* cadena, unsigned int sizeCadena , char *IPDestino, int Puerto ){
   datos = new char [sizeCadena];
   memcpy(datos,cadena,sizeCadena);
   strcpy(ip,IPDestino);
   longitud = sizeCadena ;
   puerto = Puerto;
}
/// mensaje vacio 
 PaqueteDatagrama::PaqueteDatagrama(unsigned int sizeMsg )
 {
   longitud = sizeMsg;
   datos = new char[sizeMsg];
  }
PaqueteDatagrama::~PaqueteDatagrama(){
  delete datos;
}
char* PaqueteDatagrama::obtieneDireccion(){return ip; }
unsigned int PaqueteDatagrama:: obtieneLongitud(){return longitud;}
int PaqueteDatagrama::obtienePuerto(){return puerto;}
char* PaqueteDatagrama::obtieneDatos(){return datos;}
void PaqueteDatagrama:: inicializaPuerto(int p){puerto = p;}
void PaqueteDatagrama:: inicializaIp(char *IPDestino){ strcpy(ip,IPDestino);}
void PaqueteDatagrama:: inicializaDatos(char *msg){
  memcpy(&datos,&msg,sizeof(int)*longitud);
  // printf("datos en la funcion %d ",datos);
}
std::ostream& operator<<(std::ostream& os, PaqueteDatagrama& p){
  os<<endl<<"IP: "<<p.obtieneDireccion()<<"\tPuerto :"<<p.obtienePuerto()<<"\t Tamanio mensaje : "<<p.obtieneLongitud()<<endl;
}
