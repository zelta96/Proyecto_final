#include "mongoose.h"
#include "archivo.h"
#include "Solicitud.h"
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
//gcc mongoose.c servidorHTML.c -o servidorHTML
static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
static void ev_handler(struct mg_connection *nc, int ev, void *p) {
if (ev == MG_EV_HTTP_REQUEST) {
mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
}
}
int main(void) {
struct mg_mgr mgr;
struct mg_connection *nc;
mg_mgr_init(&mgr, NULL);
printf("Starting web server on port %s\n", s_http_port);
nc = mg_bind(&mgr, s_http_port, ev_handler);
if (nc == NULL) {
printf("Failed to create listener\n");
return 1;
}
// Set up HTTP server parameters
mg_set_protocol_http_websocket(nc);
s_http_server_opts.document_root = "."; // Serve current directory
s_http_server_opts.enable_directory_listing = "yes";

//archivo
int ba = O_WRONLY|O_TRUNC|O_CREAT;
mode_t modo=0666;
Archivo info("votos.txt",ba,modo);
Solicitud solicitud;
char argumentos[4000];
char ip[16] = "127.0.0.1";
int puerto = 6300;
Solicitud peticion = Solicitud();

for (;;) {
//
memcpy(argumentos, peticion.doOperation(ip,puerto,2,0,"abc"), sizeof(argumentos));
info.escribe((void *)argumentos,strlen(argumentos));
info.destroy();
//	
mg_mgr_poll(&mgr, 10000);
}

mg_mgr_free(&mgr);
return 0;
}