#include "SocketDatagrama.h"
#include <iostream>
#include <cstring>

using namespace std;

class Solicitud{
	public:
		Solicitud();
		char * doOperation(char *IP, int puerto, int operationId, int requestId, char *arguments);
	private:
		SocketDatagrama *socketlocal;
};