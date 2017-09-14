//
// DIRETORIOS.C
//
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int pesquisa(const char *arg, const char *caminho){
    DIR *dirpont, *dirptraux;
    struct dirent *dp, *listDir;
    char *proximo;

    if ((dirpont = opendir(caminho)) == NULL) {
        (void) printf( "nao pode abrir %s \n\n", caminho);
        return 0;
    }
    do {
        errno = 0;
        if ((dp = readdir(dirpont)) != NULL) {
            if (strcmp(dp->d_name, arg) == 0){
              (void) printf("Achou: %s | Caminho: %s/%s\n", dp->d_name, caminho, dp->d_name);
              (void) closedir(dirpont);
              return 1;
            }else{
              if(dp->d_type == 4 && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
                proximo = (char *)malloc(strlen(caminho)+strlen(dp->d_name)+2); //Caminho para proxima pasta
                strcat(proximo, caminho);
                strcat(proximo,"/");
                strcat(proximo,dp->d_name);
                if(pesquisa(arg, proximo) == 1){
                  return 1;
                }
              }
            }
        }
    } while (dp != NULL);

    if (errno != 0)
        perror("Erro lendo o diretorio\n\n");
    else
        (void) printf("Falha ao procurar: %s\n", arg);
    (void) closedir(dirpont);
    return 0;
}

int main(int argc, char *argv[])
{
    int i;

    if( argc < 2 ) {
       printf( "USO: %s nome_arquivo ...\n\n", argv[ 0 ] );
       return( -1 );
    }
    for (i = 1; i < argc; i++){
        pesquisa(argv[i], ".");
    }
    return (0);
}
