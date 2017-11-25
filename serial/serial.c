#include <stdio.h>
#include <stdlib.h>
#include "rs232.c"

#ifdef __linux__                   // Verifica se tah no linux
#define limpar(x)  __fpurge(x)     // Se tiver, utiliza o __fpurge
#else                              // Se nao tiver no linux
#define limpar(x)  fflush(x)       // Utiliza fflush
#endif

#define TAM 50                         //

char string[TAM];                   // Variavel q recebe a palavra a ser enviada

int comporta, fd;

void enviar(){
  limpar(stdin);
  memset(string, 0, sizeof(string));  // limpa a string
  printf("\n> ");
  fgets(string,TAM,stdin);             // Pegar a string digitada e armazenar na variavel "string[30]"
  cprintf(comporta,string);                  // Função da biblioteca - Enviar a string via serial
  printf("Enviado com sucesso.");
}

void receber(){
  printf("\nAguardando Recebimento de Dados:");
  while(1){
    limpar(stdin);
    memset(string, 0, sizeof(string));
    PollComport(comporta, (unsigned char*)(string), 30);// Poll Comport - Função da biblioteca q recebe a string
    if(strcmp(string, "") != 0){
      printf("Recebido: %s\n",string);
    }
  }
}

void lerArquivo(){
    FILE * fp;
    char * linha = NULL;
    size_t tamanho = 0;
    ssize_t read;

    fp = fopen("notas.lst", "r");
    if (fp == NULL)
        printf("Erro ao abrir o arquivo\n");

    while ((read = getline(&linha, &tamanho, fp)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", linha);
    }
    fclose(fp);
    if (linha)
        free(linha);
}

int main (){
    int op;
    printf("Informe a porta serial: ");
    scanf("%d", &comporta);
    OpenComport(comporta,9600);            // Abrir porta COM 0 com velocidade de 9600

    while(1){
        limpar(stdin);              // Limpar o buffer
        printf("\n1 - Enviar string");
        printf("\n2 - Receber string");
        printf("\n3 - Ler Arquivo");
        printf("\n4 - Sair\n\n");

        scanf("%d",&op);

        switch(op){
            case (1): enviar();
                      break;

            case (2): receber();
                      break;

            case (3): lerArquivo();
                      break;
            case (4): CloseComport(comporta);         // Fechar a porta COM 0
                      return 0;
                      break;
        }
    }
}
