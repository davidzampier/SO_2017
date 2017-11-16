/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <assert.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

#include "server.h"

/*Parametros recebidos no GET*/
void* parametros;
char* aux_parametros;
/* A template for the HTML page this module generates.  */

static char* page_template =
  "<html>\n"
  " <head>\n"
  "  <meta http-equiv=\"refresh\" content=\"5\">\n"
  " </head>\n"
  " <body>\n"
  "  <p>ANome: %s</p>\n"
  " </body>\n"
  "</html>\n";

void module_generate (int fd)
{
  struct timeval tv;
  struct tm* ptm;
  char time_string[40];
  FILE* fp;

  /* Obtain the time of day, and convert it to a tm struct.  */
  gettimeofday (&tv, NULL);
  ptm = localtime (&tv.tv_sec);
  /* Format the date and time, down to a single second.  */
  //strftime (time_string, sizeof (time_string), "%H:%M:%S", ptm);

  /* Create a stream corresponding to the client socket file
     descriptor.  */
  fp = fdopen (fd, "w");
  assert (fp != NULL);

  fprintf(fp, "\nasfsdfsdgsg %s", parametros);
  if(parametros == NULL){
    fprintf(fp, " - 1");
  }else{
    aux_parametros = parametros;
    aux_parametros = strtok(aux_parametros, "=");
    //fprintf(fp, "\n2: %s\n\n", parametros);
    //char* ano = "-1", mes = "-1";
    //fprintf(fp, "\nEntrou2: %s \n", parametros);
    while(aux_parametros != NULL){
      //fprintf(fp, "\nEntrou2: %s\n", aux_parametros);
      //fprintf(fp, "\nEntrou2: %s\n", parametros);
      /*if(*vet_parametros == "ano"){
        vet_parametros = strtok(NULL, "=");
        ano = vet_parametros;
        fprintf(fp, "4");
      }
      if(strcmp(vet_parametros, "mes") == 0){
        vet_parametros = strtok(NULL, "=");
        mes = vet_parametros;
        fprintf(fp, "5");
      }*/
      aux_parametros = strtok(NULL, "=");
      //fprintf(fp, "6");
    }
    /*
    if(strcmp(ano, "-1") && strcmp(mes, "-1")){ //Mes e ano sao diferentes de -1
      char* argv[] = { "/usr/bin/cal", mes, ano, NULL };

    }else if(strcmp(ano, "-1")){ //Tem so ano
      char* argv[] = { "/usr/bin/cal", ano, NULL };

    }else if(strcmp(mes, "-1")){ //Tem so ano
      char* argv[] = { "/usr/bin/cal", "-m", mes, NULL };

    }*/
  }

  /* Generate the HTML output.  */
  fprintf (fp, page_template, parametros);
  /* All done; flush the stream.  */
  fflush (fp);
}
