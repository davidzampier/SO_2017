//
//  Programa utilizado para criar o arquivo com notas para processamento.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void main( void )
{
  int i, fd;

  fd = open( "notas.lst", O_WRONLY | O_CREAT | O_TRUNC, 0666 );

  if( fd < 0 ) {
    printf( "Erro na criacao do arquivo\n" );
    exit( fd );
  }

  for( i = 1; i <= 200; ++i ) {
    float n1, n2, n3;

    n1 = rand()%100/10.0;
    n2 = rand()%100/10.0;
    n3 = rand()%100/10.0;
    if( n1 + n2 >= 14.0 )
      dprintf( fd, "%d\t%4.1f\t%4.1f\t%4.1f\n", i, n1, n2, 0.0 );
    else
      dprintf( fd, "%d\t%4.1f\t%4.1f\t%4.1f\n", i, n1, n2, n3 );
  }
  close( fd );
}
