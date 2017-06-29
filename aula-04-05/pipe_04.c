#include <stdio.h> 
#include <unistd.h>
#include <stdlib.h>
//
//  comando:
//       $       cat /etc/passwd | grep home | wc
//
//   PROBLEMA:  como criar redirecionamento de/para arquivos:    cat /etc/passwd >  meu_arquivo_1
//                                                               grep home < meu_arquivo_1 > meu_arquivo_2
//                                                               wc < meu_arquivo_2
//
// 
int main(void){
  int pfd_0[2], 
      pfd_1[2],
      status;

  pipe( pfd_0 );
  pipe( pfd_1 );

#ifdef DEBUG
  printf( "PAI: pfd_0[%d:%d]\t-\tpfd_1[%d:%d]\n\n", pfd_0[0],pfd_0[1],pfd_1[0],pfd_1[1] );
#endif
  switch( fork() ){
    case -1: exit(1);
             break;
    case 0:  
#ifdef DEBUG
    printf( "FILHO 1: pfd_0[%d:%d]\t-\tpfd_1[%d:%d]\n\n", pfd_0[0],pfd_0[1],pfd_1[0],pfd_1[1] );
#endif
             close( 0 );
             dup2( pfd_0[ 0 ], 0 );
             close( pfd_0[ 0 ] );
             close( pfd_0[ 1 ] );
             close( pfd_1[ 0 ] );
             close( pfd_1[ 1 ] );
             execl( "/usr/bin/wc", "wc", 0 );  // como colocar parametro para contar linhas apenas?
             break;
  }

  switch( fork() ){
    case -1: exit(1);
             break;
    case 0:  
#ifdef DEBUG
   printf( "FILHO 2: pfd_0[%d:%d]\t-\tpfd_1[%d:%d]\n\n", pfd_0[0],pfd_0[1],pfd_1[0],pfd_1[1] );
#endif
             close( 0 );
             dup2( pfd_1[ 0 ], 0 );
             close( 1 );
             dup2( pfd_0[ 1 ], 1 );
             close( pfd_0[ 0 ] );
             close( pfd_0[ 1 ] );
             close( pfd_1[ 0 ] );
             close( pfd_1[ 1 ] );
             execl( "/bin/grep", "grep", "home", 0 );
             break;
  }

   
  switch( fork() ) {
    case -1: exit(1);
             break;
    case 0:  
#ifdef DEBUG
   printf( "FILHO 3: pfd_0[%d:%d]\t-\tpfd_1[%d:%d]\n\n", pfd_0[0],pfd_0[1],pfd_1[0],pfd_1[1] );
#endif
             close( 1 );
             dup2( pfd_1[ 1 ], 1 );
             close( pfd_0[ 0 ] );
             close( pfd_0[ 1 ] );
             close( pfd_1[ 0 ] );
             close( pfd_1[ 1 ] );
             execl( "/bin/cat", "cat", "/etc/passwd", 0);
             break;
  }
  wait(&status);
  return 0;
}
