#include <iostream>
#include <string>
#include <vector>
#include "PaqueteDatagrama.h"
#include "SocketDatagrama.h"
#include "Searcher.h"

#include <cstring>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <vector>
#include <sstream>

using namespace std;

struct operacion{
	int op;
	int v1;
	int v2;
	char arg[255];
};


std::vector<std::string> split(std::string strToSplit, char delimeter)
{
    std::stringstream ss(strToSplit);
    std::string item;
    std::vector<std::string> splittedStrings;
    while (std::getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}


string Freversa(string p){
 string r;
 for(int i = p.size()-1; i >= 0; i--)
  r += p[i];
 return r;
}

int palindromo(string palabra){
    int l = 0, h = palabra.length(); 
   
    for (int i = 0; i < h; i++) 
        palabra[i] = tolower(palabra[i]); 
   
    while (l <= h) { 


   
        if (!(palabra[l] >= 'a' && palabra[l] <= 'z')) 
            l++; 
   

        else if (!(palabra[h] >= 'a' && palabra[h] <= 'z')) 
            h--; 
   
        else if (palabra[l] == palabra[h]) 
            l++, h--; 

        else
            return 1;
    } 
   
    return 0; 

}

void getCurrentAddr(char * res){
	int fd;
    struct ifreq ifr;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name, "wlp3s0", IFNAMSIZ-1);
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    
	//inet_ntop(AF_INET, &(msg_to_client_addr.sin_addr), buffer, 20);
    inet_ntop(AF_INET, &(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), res, INET_ADDRSTRLEN);

    return;
}

int main(int argc, char const *argv[]){
	bool soynuevo = true;
	SocketDatagrama s_send(0);
	SocketDatagrama s_recv(9444);
	s_send.activaBroadcast(true);
	struct operacion data_ping = {0,0,0,""};
	char broadcast[16] = "255.255.255.255";
	PaqueteDatagrama p1((char*)&data_ping,sizeof(data_ping),broadcast,9444);
	s_send.envia(p1);
	while(1){	
		//cout << "Esperando comando...";
		PaqueteDatagrama p3(sizeof(struct operacion));
		s_recv.recibe(p3);
		char buff[20];
		getCurrentAddr(buff);
		if(!strcmp(p3.obtieneDireccion(),buff)) {
			cout << "Auto-ping."<< endl <<"Buscando otros nodos..." << endl;
			continue;
		}
		struct operacion op_recv;
		memcpy(&op_recv, p3.obtieneDatos(), sizeof(struct operacion));

		switch(op_recv.op){
			case 0: { // Ping
				cout << "Recibi Ping ";
				struct operacion ping_reply = {0,1,0,""};
				PaqueteDatagrama p4((char*)&ping_reply,sizeof(struct operacion),p3.obtieneDireccion(),9444);
				if(op_recv.v1 == 0)	{
					cout << "Request - Enviando Reply" << endl;
					s_send.envia(p4);					
				}else{
					cout << "Reply de " << p3.obtieneDireccion() << endl;
					if(soynuevo){
						char  comando[120];
						sprintf(comando,"wget -R index.html -np -r http://%s:8000/ -P . -nH --cut-dirs=1 -P ./ARCHIVOS/",p3.obtieneDireccion());
						cout << comando << endl;
						system(comando);
						soynuevo = false;
					}
				}
				break;
			}
			case 1: { // Busqueda
				cout << "Recibi Query ["<< op_recv.arg <<"] Buscando..." << endl;
				/*createIndex();
				vector<pair<string,pair<int,int> > > found;
				string arg(op_recv.arg);
				found = searchInIndexFileByParts("INDEXFILE",arg,op_recv.v1,op_recv.v2);
				struct operacion encontrado;
				for(int i=0; i<found.size(); i++) {
					encontrado.op  = 2;
					encontrado.v1  = found[i].second.first;
					encontrado.v2  = found[i].second.second;
					memcpy(encontrado.arg,found[i].first.c_str(),found[i].first.size()+1);
					PaqueteDatagrama p5((char*)&encontrado,sizeof(struct operacion),p3.obtieneDireccion(),9444);
					s_send.envia(p5);
				}*/

				int limiteMin;
  				int limiteMax;
				limiteMax=(int) *op_recv.arg;

				 ifstream ficheroEntrada;
				string frase;
 				ficheroEntrada.open ("doc.txt");
				 getline(ficheroEntrada, frase);
 				ficheroEntrada.close();
 				int countChar = frase.length();

         
				 cout << "Frase leida: " << countChar << endl;

				vector<string> v = split (frase, '-');

				string resultadoCadena;
int ndoble = 34911;
for (int k = 0; k < 34911; k++)
{
  
for (int i = 0; i < v.size() - ndoble  ; i++)
{
  for (int j = i; j < i + ndoble     ; j++)
  {
   
    resultadoCadena = resultadoCadena + v[j];
   //  cout << "Palabra analizads: " << resultadoCadena << endl;
  }
  if(Freversa(resultadoCadena)==resultadoCadena){

    cout << "Encontrado Palindromo: " << resultadoCadena << endl;
    resultadoCadena = "";
  }
  else{
    resultadoCadena = "";
  }
  
}

ndoble--;
if (ndoble==1)
{
  break;
}

}
cout << "tamaño std::vector<char> v;: " << v.size() << endl;
    cout << "\nCalculando" << endl;

				cout << "Encontradas " << limiteMax << " coincidencias." << endl;
				/*encontrado.op  = 3;
				encontrado.v1  = 0;
				encontrado.v2  = 0;
				memcpy(encontrado.arg,"END",4);

				PaqueteDatagrama p6((char*)&encontrado,sizeof(encontrado),p3.obtieneDireccion(),p3.obtienePuerto());
				s_send.envia(p6);*/
				break;
			}
			case 4: {
				char comando[120];
				sprintf(comando,"curl http://%s:8000/text/%s --output ./ARCHIVOS/%s",p3.obtieneDireccion(),op_recv.arg,op_recv.arg);
				system(comando);
				break;
			}
		}
	}

	return 0;
}