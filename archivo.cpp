#include <string>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include<stdio.h>
#include "archivo.h"

using namespace std;

Archivo::Archivo(string filename){
	num_bytes=0;
	nombreArchivo=filename;
	fd=open(nombreArchivo.c_str(),O_RDONLY);
}

Archivo::Archivo(string filename,int banderas, mode_t modo){
	num_bytes=0;
	nombreArchivo=filename;
	fd=open(nombreArchivo.c_str(),banderas,modo);
}

size_t Archivo::lee(size_t nbytes){
	if(num_bytes>1){
		contenido=(char*)realloc(contenido,nbytes+num_bytes);
	}else{
		contenido=(char*)malloc(nbytes);		
	}
	num_bytes+=read(fd,contenido+num_bytes,nbytes);
	contenido=(char*)realloc(contenido,num_bytes);
	return num_bytes;
}

size_t Archivo::escribe(void *buffer, size_t nbytes){
	if(num_bytes>1){
		contenido=(char*)realloc(contenido,nbytes+num_bytes);
	}else{
		contenido=(char*)malloc(nbytes);		
	}
	num_bytes=write(fd, buffer, nbytes);
	return num_bytes;
}

size_t Archivo::obtieneNum_bytes(){
	return num_bytes;
}

const char* Archivo::get_contenido(){
	return contenido;
}
void Archivo::destroy(){
	close(fd);
	if(num_bytes>2)
	delete[] contenido;
}
Archivo::~Archivo(){
	close(fd);
	if(num_bytes>2)
	delete[] contenido;
}

