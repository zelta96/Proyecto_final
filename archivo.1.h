#ifndef ARCHIVO_H_
#define ARCHIVO_H_
#include <string>
#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <cstddef>
using namespace std;
class Archivo
{
private:
string nombreArchivo;
int fd;
char *contenido;
size_t num_bytes;
public:
Archivo(string filename);
Archivo(string filename, int banderas, mode_t modo);
size_t lee(size_t nbytes);
size_t escribe(void *buffer, size_t nbytes);
size_t obtieneNum_bytes();
void destroy();
const char *get_contenido();
~Archivo();
};
#endif
