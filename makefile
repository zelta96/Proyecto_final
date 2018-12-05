ServidorHTML: servidorHTML.c PaqueteDatagrama.o SocketDatagrama.o Solicitud.o archivo.o
	g++ mongoose.c servidorHTML.c PaqueteDatagrama.o SocketDatagrama.o Solicitud.o archivo.o -o servidorHTML
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h 
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c	
archivo.o: archivo.cpp archivo.h
	g++ archivo.cpp -c
